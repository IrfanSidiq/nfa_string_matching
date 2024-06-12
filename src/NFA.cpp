#include "../include/NFA.h"

NFA::NFA(std::string pattern)
{
    this->pattern = pattern;
    graph = Graph(pattern.length() + 1);    // plus final state as last node

    for (int i = 0; i < (int) pattern.length(); i++)
    {
        if (pattern[i] == '*')
        {
            graph.addEdge(i, i+1);
            graph.addEdge(i+1, i);
        }
    }
}

bool NFA::accepts(std::string text)
{
    std::vector<int> expandNodes; 
    std::unordered_set<int> visited;

    // Do epsilon transition before matching text to find all possible starting states
    DFS(graph, 0, visited);
    for (int node : visited)
    {
        expandNodes.push_back(node);
    }

    std::vector<int> nextExpandNodes;

    // Start matching DFA with text
    for (int i = 0; i < (int) text.length(); i++)
    {
        nextExpandNodes.clear();
        for (int node : expandNodes)
        {
            if (pattern[node] == text[i] || pattern[node] == '?' || pattern[node] == '*')
            {
                nextExpandNodes.push_back(node + 1);
            }
        }

        // Do epsilon transition for next expand states
        visited.clear();
        for (int nodes : nextExpandNodes)
        {
            DFS(graph, nodes, visited);
        }

        expandNodes.clear();
        for (int node : visited)
        {
            expandNodes.push_back(node);
        }
    }

    // After matching the entire text, check if final state is reached
    int finalState = graph.getNumOfNodes() - 1;
    for (int node : expandNodes)
    {
        if (node == finalState)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::pair<int, std::string>> NFA::find(std::string text)
{
    std::vector<std::pair<int, std::string>> result;
    
    // Finds first char in pattern that's not a wildcard
    int patternStart = 0, numOfAnyCharsInPrefix = 0;
    while (patternStart < pattern.length() && (pattern[patternStart] == '*' || pattern[patternStart] == '?'))
    {
        if (pattern[patternStart] == '?')
        {
            numOfAnyCharsInPrefix++;
        }
        patternStart++;
    }

    if (patternStart == pattern.length())
    {
        if (text.length() > numOfAnyCharsInPrefix)
        {
            result.push_back(std::make_pair(0, text));
        }
        return result;
    }

    // Finds last char in pattern that's not a wildcard
    int patternEnd = pattern.length() - 1, numOfAnyCharsInSuffix = 0;
    while (patternEnd > patternStart && (pattern[patternEnd] == '*' || pattern[patternEnd] == '?'))
    {
        if (pattern[patternEnd] == '?')
        {
            numOfAnyCharsInSuffix++;
        }
        patternEnd--;
    }
    
    int textStart = numOfAnyCharsInPrefix;
    while (textStart < text.length())
    {
        bool found = false;
        // Finds char in string that matches the first non-wildcard char in pattern
        while (textStart < text.length() && text[textStart] != pattern[patternStart])
        {
            textStart++;
        }
        if (textStart == text.length())
        {
            return result;
        }

        int textEnd = textStart;
        while (textEnd < text.length())
        {
            // Finds char in string that matches the last non-wildcard char in pattern
            while (textEnd < text.length() && text[textEnd] != pattern[patternEnd])
            {
                textEnd++;
            }
            if (textStart == text.length() || text.length() - textEnd - numOfAnyCharsInSuffix < 0)
            {
                break;
            }

            textStart -= numOfAnyCharsInPrefix;
            textEnd += numOfAnyCharsInSuffix;
            std::string substring = text.substr(textStart, textEnd - textStart + 1);
            
            if (accepts(substring))
            {
                result.push_back(std::make_pair(textStart, substring));
                found = true;
                break;    
            }

            textEnd++;
        }
        
        if (found)
        {
            textStart = textEnd + numOfAnyCharsInPrefix;
        }
        textStart++;
    }

    return result;
}

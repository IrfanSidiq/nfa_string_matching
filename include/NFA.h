#ifndef NFA_H
#define NFA_H

#include <string>

#include "../include/DFS.h"

class NFA
{
    private:
        Graph graph;
        std::string pattern;

    public:
        // Builds a NFA graph with its epsilon transitions
        NFA(std::string pattern);

        // Returns true if NFA accepts the text
        bool accepts(std::string text);

        /** Finds matching substrings in text
         * @return Pairs of matched substrings and its indexes
        */
        std::vector<std::pair<int, std::string>> find(std::string text);
};

#endif
#include <iostream>
#include <exception>
#include <limits>
#include <chrono>

#include "../include/Program.h"
#include "../include/NFA.h"

void Program::run()
{
    std::cout << "Welcome to wildcard string matcher with NFA!" << std::endl;
    std::cout << "Select your matching criteria:" << std::endl;
    std::cout << " ____________________________\n";
    std::cout << "| 1. Exact match             |\n";
    std::cout << "| 2. Find substring matches  |\n";
    std::cout << " ----------------------------" << std::endl;

    int chosenCriteria = validateIntegerInput(1, 2);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string text;
    std::cout << "\nEnter text input: ";
    std::getline(std::cin, text);

    std::string pattern;
    std::cout << "\nEnter pattern to be matched: ";
    std::getline(std::cin, pattern);
    std::cout << std::endl;

    NFA nfa = NFA(pattern);
    auto start = std::chrono::high_resolution_clock::now();
    switch (chosenCriteria)
    {
        case 1:
            if (nfa.accepts(text))
            {
                std::cout << "Pattern matches!" << std::endl;
            }
            else
            {
                std::cout << "Pattern did not match." << std::endl;
            }
            break;

        case 2:
            std::vector<std::pair<int,std::string>> results = nfa.find(text);
            if (results.size() == 0)
            {
                std::cout << "Found no matching substrings." << std::endl;
            }
            else
            {
                std::cout << "Found " << results.size() << " matching substrings:" << std::endl;
                for (int i = 0; i < (int) results.size(); i++)
                {
                    std::cout << i+1 << ") Index [" << results[i].first << "-" << results[i].first + results[i].second.length() - 1
                        << "]: \"" << results[i].second << "\"" << std::endl;
                }
            }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "\nExecution time: " << duration.count() << " ms" << std::endl;
    std::cout << std::endl;
}

int Program::validateIntegerInput(int lowerBound, int upperBound) {
    int chosenCriteria;
    bool inputValid = false;
    while (!inputValid)
    {
        std::cout << "\nYour input: ";
        try {
            std::cin >> chosenCriteria;

            if (chosenCriteria < 1 || chosenCriteria > 2)
            {
                throw std::exception();
            }
            
            inputValid = true;
        }
        catch (std::exception _)
        {
            std::cout << "Chosen number is not valid!" << std::endl;
        }
    }

    return chosenCriteria;
}
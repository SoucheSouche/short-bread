#ifndef CONSTANTS_H
#define COSNTANTS_H

#include <string>
#include <vector>

/**
 * @brief URL of the dictionnary used by the algorithm
 */
const std::string csDictionnaryUrl = "https://www.wordgamedictionary.com/enable/download/enable.txt";

/**
 * @brief The english alphabet letter sorted from the least used to the most used letter
 * @note This alphabet is sorted this way to minimize the parsing of deadend branches during
 * the graph parsing.
 */
const std::vector<char>
    csAlphabet = {'q', 'j', 'z', 'x', 'v', 'k', 'w', 'y', 'f', 'b', 'g', 'h', 'm',
                  'p', 'd', 'u', 'c', 'l', 's', 'n', 't', 'o', 'i', 'r', 'a', 'e'};

#endif // CONSTANTS_H

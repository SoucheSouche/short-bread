#include <algorithm>
#include <iostream>

#include "Constants.h"
#include "Dictionnary.h"
#include "ShortBread.h"

std::mutex ShortBread::mutex{};

void ShortBread::init()
{
    std::cout << "Initialization..." << std::endl;
    try
    {
        Dictionnary::init(csDictionnaryUrl);
    }
    catch (const std::exception &e)
    {
        throw;
        std::cout << "Initialization failure." << std::endl;
    }
    std::cout << "Initialization success" << std::endl;
}

std::vector<std::string> ShortBread::getResult(const std::string &csStartWord, const std::string &csEndWord)
{
    mutex.lock();

    std::vector<std::string> result{};
    result.clear();

    // check if the input words size matches as a solution does not exist for 2 words with different length.
    if (csStartWord.size() != csEndWord.size())
    {
        return result;
    }

    // ad the start word to the result
    result.push_back(csStartWord);

    // std::vector<std::string> subset = Dictionnary::getDictionnarySubset(csEndWord.size());
    // std::cout << subset.size() << std::endl;
    // for (auto &it : subset)
    // {
    //     std::cout << it << std::endl;
    // }

    // execute the recursive algo to try and find a solution to the shortbread problem
    std::size_t letterPosition = 0;
    shortBreadAlgo(result, csEndWord, letterPosition);

    mutex.unlock();

    return result;
}

void ShortBread::shortBreadAlgo(std::vector<std::string> &oResult, const std::string &csEndWord,
                                std::size_t &letterPosition)
{
    if (0 == oResult.back().compare(csEndWord))
    {
        return;
    }

    // get through the letters from the alphabet
    for (std::size_t iPosition = 0; iPosition < csEndWord.size(); iPosition++)
    {
        std::vector<char> availableLetters = csAlphabet;
        char targetLetter = csEndWord.at(iPosition);
        auto targetLetterIt = std::find(availableLetters.begin(), availableLetters.end(), targetLetter);
        availableLetters.erase(targetLetterIt);
        availableLetters.push_back(targetLetter);
        if (oResult.back().at(iPosition) == csEndWord.at(iPosition))
        {
            continue;
        }
        for (std::vector<char>::reverse_iterator itLetter = availableLetters.rbegin(); itLetter != availableLetters.rend(); itLetter++)
        {
            std::string newWord = oResult.back();
            newWord.at(iPosition) = *itLetter;
            if (Dictionnary::belongsTo(newWord) && std::find(oResult.begin(), oResult.end(), newWord) == oResult.end())
            {
                oResult.push_back(newWord);
                if (newWord == csEndWord)
                {
                    return;
                }
                shortBreadAlgo(oResult, csEndWord, letterPosition);
                if (oResult.back() == csEndWord)
                {
                    return;
                }
            }
            else
            {
                // continue with a new letter
            }
        }
    }
    oResult.pop_back();
}
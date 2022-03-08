#include <algorithm>
#include <iostream>

#include "Constants.h"
#include "Dictionnary.h"
#include "ShortBread.h"

std::mutex ShortBread::mutex{};

void ShortBread::init()
{
    std::cout << "Initialization..." << std::endl;
    mutex.lock();
    try
    {
        Dictionnary::init(csDictionnaryUrl);
    }
    catch (const std::exception &e)
    {
        mutex.unlock();
        throw;
        std::cout << "Initialization failure." << std::endl;
    }
    mutex.unlock();
    std::cout << "Initialization success" << std::endl;
}

std::vector<std::string> ShortBread::getResult(const std::string &csStartWord, const std::string &csEndWord)
{
    mutex.lock();

    std::vector<std::string> result{};
    result.clear();

    // check if the input words size matches as a solution does not exist for 2 words with different length.
    // also check that both words belongs to the dictionnary
    if (csStartWord.size() != csEndWord.size() ||
        !Dictionnary::belongsTo(csStartWord) ||
        !Dictionnary::belongsTo(csEndWord))
    {
        return result;
    }

    // ad the start word to the result
    result.push_back(csStartWord);

    // execute the recursive algo to try and find a solution to the shortbread problem
    std::size_t letterPosition = 0;
    shortBreadAlgo(result, csEndWord, letterPosition);

    mutex.unlock();

    return result;
}

void ShortBread::shortBreadAlgo(std::vector<std::string> &oResult, const std::string &csEndWord, std::size_t &letterPosition)
{
    if (0 == oResult.back().compare(csEndWord))
    {
        return;
    }

    // get through the letters from the alphabet
    for (std::size_t iPosition = 0; iPosition < csEndWord.size(); iPosition++)
    {
        // store the target value from the end word first in the alphabet
        // to avoid having to try unecessary branches if possible
        std::vector<char> availableLetters = csAlphabet;
        char targetLetter = csEndWord.at(iPosition);
        auto targetLetterIt = std::find(availableLetters.begin(), availableLetters.end(), targetLetter);
        availableLetters.erase(targetLetterIt);
        availableLetters.push_back(targetLetter);

        // check if a letter can be skiped in the trying process.
        // If all letters from the first one to the current one included
        //  are matching the end word, skip the current letter
        bool bSkipLetter = true;
        for (std::size_t iLetter = 0; iLetter <= iPosition; iLetter++)
        {
            if (oResult.back().at(iLetter) != csEndWord.at(iLetter))
            {
                bSkipLetter = false;
                break;
            }
        }
        if (bSkipLetter || (iPosition == letterPosition))
        {
            continue;
        }

        for (std::vector<char>::reverse_iterator itLetter = availableLetters.rbegin(); itLetter != availableLetters.rend(); itLetter++)
        {
            // create a new word from the last word in the result vector by changing one letter in the word
            std::string newWord = oResult.back();
            newWord.at(iPosition) = *itLetter;

            // if the new word belongs to dictionary and is not already in the result vector
            // add it to the vector and cal recursively the shortBreadAlgo() method
            if (Dictionnary::belongsTo(newWord) && std::find(oResult.begin(), oResult.end(), newWord) == oResult.end())
            {
                // add word to result
                oResult.push_back(newWord);

                // remember the position of the letter that lead to the new word
                // to avoid changing it again in the next shortBreadAlgo() call
                letterPosition = iPosition;

                // recursive call with updated parameters
                shortBreadAlgo(oResult, csEndWord, letterPosition);

                // check if the last added word is the end word
                // this will allow the recursive function to come back to its former call and exit
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
    // if shortBreadAlgo() exit without having found the end word, remove the last word in result before returning
    // change the value of the letterPosaition si it doesn't match the iPosition from the previous call.
    letterPosition--;
    oResult.pop_back();
}
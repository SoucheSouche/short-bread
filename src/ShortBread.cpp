#include "Constants.h"
// #include "Dictionnary.h"
#include "ShortBread.h"

std::mutex ShortBread::mutex{};

void ShortBread::init()
{
    try
    {
        Dictionnary::init(csDictionnaryUrl);
    }
    catch (const std::exception &e)
    {
        throw;
    }
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

    std::size_t letterPosition = 0;
    // ad the start word to the result
    result.push_back(csStartWord);

    // execute the recursive algo to try and find a solution to the shortbread problem
    shortBreadAlgo(result, csStartWord, csEndWord, letterPosition);

    mutex.unlock();

    return result;
}

void ShortBread::shortBreadAlgo(std::vector<std::string> &oResult, const std::string &csStartWord, const std::string &csEndWord, std::size_t &letterPosition)
{
    if (0 == csStartWord.compare(csEndWord) || csStartWord.size() <= letterPosition)
    {
        return;
    }

    // create a new word from the csStartWord by switching the letter at letterPosition to match the one from csEndWord.
    // if the letter from the start word and the end word are same at the letterPosition, just call the shortBreadAlgo() with updated parameters
    if (csStartWord.at(letterPosition) == csEndWord.at(letterPosition))
    {
        letterPosition++;
        shortBreadAlgo(oResult, csStartWord, csEndWord, letterPosition);
    }
    else
    {
        std::string newWord = csStartWord;
        newWord.at(letterPosition) = csEndWord.at(letterPosition);

        // check if the new word belongs to the dictionary and add it to the vector result if it does.
        // call the shortBreadAlgo() with updated parameters
        if (Dictionnary::belongsTo(newWord))
        {
            oResult.push_back(newWord);
            letterPosition++;
            shortBreadAlgo(oResult, newWord, csEndWord, letterPosition);
        }
    }
}
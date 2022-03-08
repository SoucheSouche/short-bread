#ifndef SHORTBREAD_H
#define SHORTBREAD_H

#include <mutex>
#include <string>
#include <vector>

class ShortBread
{
public:
    /**
     * @brief Initialize the  library. Downloads the dictionnary and sort it
     */
    static void init();

    /**
     * @brief Get the vector words solving the shortbread problem given the start and end words passed as parameters
     *
     * @param csStartWord The starting word
     * @param csEndWord The target word
     * @return std::vector<std::string> Vector of words leading from the start word to the the end word
     * (both start and end words are included in the vector). Returns empty vector if no solution was found.
     */
    static std::vector<std::string> getResult(const std::string &csStartWord, const std::string &csEndWord);

private:
    static std::mutex mutex;

    /**
     * @brief Recursive method building the result vector given the start and end words passed as parameters.
     *
     * @param oResult The output result containing the words to solve the shortbread problem
     * @param csEndWord The target word
     * @param letterPosition The current starting letter position in the recursive algo process
     */
    static void shortBreadAlgo(std::vector<std::string> &oResult, const std::string &csEndWord, std::size_t &letterPosition);
};

#endif // SHORTBREAD_H
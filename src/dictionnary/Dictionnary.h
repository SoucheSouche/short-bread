#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include <map>
#include <string>
#include <vector>

class Dictionnary
{
public:
    /**
     * @brief Retreive the dictionnary file from the given url.
     *
     * @param csDictionnaryUrl The URL from which to get the dictionnary file
     * @note Throws an invalid_argument exception if the retrieval of the dictionary file is unsuccessful
     */
    static void init(const std::string &csDictionnaryUrl);

    /**
     * @brief Get a subset of the downloaded dictionnary by length of words.
     *
     * @param cWordLength The length of words defining the dictionary subset to get
     * @return std::vector<std::string> The dictionnary subset containing all words of a given length
     */
    static std::vector<std::string> getDictionnarySubset(const std::size_t cWordLength);

    /**
     * @brief return the information whether a word belongs to the dictionnary or not.
     *
     * @param csWord The word to check against the dictionnary
     * @return true The word belongs to the dictionnary
     * @return false The word doesn't belong to the dictionnary
     */
    static bool belongsTo(const std::string &csWord);

private:
    /**
     * @brief Indicate whether the static class was initialized or not.
     * Used to prevent execution of public method before initialization.
     */
    static bool bIsInitialized;

    /**
     * @brief Number of bytes received from the http request
     */
    static std::size_t byteReceived;

    /**
     * @brief Subset map of the dictionnary where the size of word is the key
     */
    static std::map<std::size_t, std::vector<std::string>> subsetDictionnary;

    /**
     * @brief Get the dictionary file from the given URL.
     *
     * @param csDictionnaryUrl The URL from where to get the dictionary file
     * @return The operation status (true for success, false for failure)
     */
    static bool getFile(const std::string &csDictionnaryUrl);

    /**
     * @brief Sort the dictionnary by length of words.
     *
     * @param csDictionnaryStream The string response from the http get request.
     */
    static void sortDictionnary(const std::string &csDictionnaryStream);

    /**
     * @brief Check that the class was initialized and throws a logic_error excpetion if not.
     */
    static void initializationCheck();

    /*!
     * @brief Callback to fill user buffer with data from ACM
     *
     * @param pData
     * @param size
     * @param nmemb
     * @param pUserBuffer
     * @return std::size_t
     */
    static std::size_t writeCallback(const void *pData, std::size_t size, std::size_t nmemb, std::string *pUserBuffer);
};

#endif // DICTIONNARY_H
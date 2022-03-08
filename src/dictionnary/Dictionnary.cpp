#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <curl/curl.h>

#include "Dictionnary.h"

bool Dictionnary::bIsInitialized = false;
std::size_t Dictionnary::byteReceived = 0;
std::map<std::size_t, std::vector<std::string>> Dictionnary::subsetDictionnary{};

void Dictionnary::init(const std::string &csDictionnaryUrl)
{
    if (!getFile(csDictionnaryUrl))
    {
        throw std::invalid_argument("Could not retreive the dictionnary from: " + csDictionnaryUrl);
    }
    bIsInitialized = true;
}

const std::vector<std::string> &Dictionnary::getDictionnarySubset(const std::size_t cWordLength)
{
    initializationCheck();
    return subsetDictionnary[cWordLength];
}

bool Dictionnary::belongsTo(const std::string &csWord)
{
    initializationCheck();
    bool bRetVal = false;
    const std::vector<std::string> &subset = getDictionnarySubset(csWord.size());
    if (std::find(subset.begin(), subset.end(), csWord) != subset.end())
    {
        bRetVal = true;
    }
    return bRetVal;
}

bool Dictionnary::getFile(const std::string &csDictionnaryUrl)
{
    bool bRetVal = false;

    CURL *curl;
    CURLcode res;
    std::string sDictionnaryStream;

    curl = curl_easy_init();

    if (curl)
    {
        (void)curl_easy_setopt(curl, CURLOPT_URL, csDictionnaryUrl.c_str());
        (void)curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Dictionnary::writeCallback);
        (void)curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sDictionnaryStream);
        (void)curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 20000);
        res = curl_easy_perform(curl);

        byteReceived = 0;

        if (res == CURLE_OK)
        {
            sortDictionnary(sDictionnaryStream);
            bRetVal = true;
        }

        curl_easy_cleanup(curl);
    }

    return bRetVal;
}

std::size_t Dictionnary::writeCallback(const void *pData, std::size_t size, std::size_t nmemb, std::string *pUserBuffer)
{
    std::size_t sizeOfData = size * nmemb;

    (void)pUserBuffer->append(static_cast<const char *>(pData), size * nmemb);
    byteReceived += sizeOfData;

    return sizeOfData;
}

void Dictionnary::sortDictionnary(const std::string &csDictionnaryStream)
{
    std::stringstream ss(csDictionnaryStream);
    std::string word;
    while (ss >> word)
    {
        subsetDictionnary[word.size()].push_back(word);
    }
}

void Dictionnary::initializationCheck()
{
    if (!bIsInitialized)
    {
        throw std::logic_error("Trying to access a Dictionnary method before initialization");
    }
}
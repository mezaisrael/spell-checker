//Israel Meza
#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <fstream>
#include <string>

class SpellChecker
{
public:
    //contructor for hash dictionary
    SpellChecker(const std::string &fileToCheck, const std::string& dictionary);

    void dictionaryFileToHash(const std::string &dictionary, std::unordered_set<std::string> &dictionaryHash);

    //return vector of the words in the file
    std::vector<std::string> parseText(const std::string &fileName);

    //returns vector of incorrect words
    std::vector<std::string> incorrectWords();

    //checks spelling
    void checkSpelling();

    void printDict();
private:
    //hash dictionay
    std::unordered_set<std::string> hashDict;

    //words in the text
    std::vector<std::string> wordsInText;

    //check if the misspell word is missing a letter
    void checkMissingLetter(const std::string &wrongWord, std::vector<std::string> &suggestions);
    
    //check if the word possibly has an extra letter and adds it to @param suggestions
    void checkExtraLetter(const std::string &wrongWord, std::vector<std::string> &suggestions);

    //check for error with replacing one letter at each position
    void checkReplaceLetter(const std::string &wrongWord, std::vector<std::string> &suggestions);
   
    //check for error caused by swapped with neighbor
    void checkSwappedWithNeighbor(std::string &wrongWord, std::vector<std::string> &suggestions);

    //return true if the word is in the dictionary false otherwise
    //this is the look up that we will performe several times and will
    //propbably determine the time O(1)
    bool isWord(std::string word){ return hashDict.count(word) == 1;}
    
};

#endif
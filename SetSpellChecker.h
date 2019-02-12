//Israel Meza
#ifndef SET_SPELL_CHECKER_H
#define SET_SPELL_CHECKER_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <fstream>
#include <string>

class SetSpellChecker
{
public:
    //contructor for map/set dictionary
    SetSpellChecker(std::string &fileToCheck, const std::string &dictionary);

    void dictionaryFileToSet(const std::string &dictionary, std::set<std::string> &dictionaryFile);

    //return vector of the words in the file
    std::vector<std::string> parseText(std::string &fileName);

    //returns vector of incorrect words
    std::vector<std::string> incorrectWords();

    //checks spelling
    void checkSpelling();

    void printDict();
private:
    //set/AVL dictionary
    std::set<std::string> setDict;

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
    //this is the look up that we will perform several times
    // O(logN)
    bool isWord(std::string word){ return setDict.count(word) == 1;}
    
};

#endif
//Israel Meza
#ifndef SPELL_CHEKCER_CPP
#define SPELL_CHEKCER_CPP

#include "SpellChecker.h"

//contructor for hash dictionary
 SpellChecker::SpellChecker(const std::string &fileToCheck, const std::string& dictionary) { 
    wordsInText = parseText(fileToCheck);

    dictionaryFileToHash(dictionary, hashDict);
}

//@param dictionay is the name of the dictionary file
//@param dictionayHash is the unordred set that will contain the dicitionay words
void SpellChecker::
dictionaryFileToHash(const std::string &dictionary, std::unordered_set<std::string> &dictionaryHash){
    std::string word;
    std::ifstream dictionaryFile (dictionary);

    if (dictionaryFile.is_open()) {
        while ( getline (dictionaryFile,word) ) {
            dictionaryHash.insert(word);
        }
        dictionaryFile.close();
    }
    else {
       std::cout << "Unable to open file " <<  dictionary << std::endl;
    } 
}

//return a vector of words that are misspelled
std::vector<std::string> SpellChecker::parseText(const std::string &fileName) {
    std::vector<std::string> words;
    std::string word;
    std::ifstream ifText(fileName);
    char character;

    if (ifText.is_open()) {
        while ( ifText.get(character) ) {
            //if its a letter keep building a word
            if( (97 <= character && character <= 122) || (67 <= character  && character <= 90) || character == '\''){
                word+=character;
            } else if(word != "") {
                words.push_back(word);
                word = "";
            }
        }

        if(word != "") {
            words.push_back(word);
        }

        ifText.close();
    }
    else {
       std::cout << "Unable to open file " <<  fileName << std::endl;
    }
    return words;
}

void SpellChecker::checkSpelling() {
    std::vector<std::string> misspelledWords = incorrectWords();
    std::vector<std::string> suggestions;

    std::ofstream ofs("unordered-test.txt", std::ofstream::out);

    for (unsigned int i = 0; i < misspelledWords.size(); ++i){
        ofs << "checking: " << misspelledWords.at(i) << " suggestions: ";
        checkMissingLetter(misspelledWords.at(i), suggestions);
        checkExtraLetter(misspelledWords.at(i), suggestions);
        checkReplaceLetter(misspelledWords.at(i), suggestions);
        checkSwappedWithNeighbor(misspelledWords.at(i), suggestions);

        for(auto suggestion : suggestions) {
            ofs << suggestion << ", ";
        }

        ofs << std::endl;

        //clear suggestion so that we can use it for the next word
        suggestions.clear();
    }

    ofs.close();
}

//return suggestions if the wrong word had a missing letter
void SpellChecker::
checkMissingLetter(const std::string &wrongWord_, std::vector<std::string> &suggestions){
    //try adding every letter in alphabet into every position of the word

    for(int i = 97; i <= 122; ++i){
        std::string wrongWord = wrongWord_;
        //character will be a-z
        std::string character(1, char(i));    
       
        //firt insert char at the begining of the word
        wrongWord.insert(0,character);
        
        if (isWord(wrongWord)) {
            suggestions.push_back(wrongWord);
        }

        //now try putting the added char into every position
        for (unsigned int i = 0; i < wrongWord.size()-1; ++i)
        {
            std::swap(wrongWord.at(i),wrongWord.at(i+1));
            if (isWord(wrongWord))
            {
                suggestions.push_back(wrongWord);
            }
        }
    }
}

//return suggestions for the word by removing one letter from the word at each position
void SpellChecker::
checkExtraLetter(const std::string &wrongWord_, std::vector<std::string> &suggestions){
    std::string modWord;

    for (unsigned int i = 0; i < wrongWord_.size(); ++i)
    {
            //make copy to modify
            modWord = wrongWord_;
            modWord.erase(modWord.begin()+i);

            if (isWord(modWord))
            {
                suggestions.push_back(modWord);
            }
    }

}

void SpellChecker::
checkReplaceLetter(const std::string &wrongWord_, std::vector<std::string> &suggestions) {
    std::string modWord;

    for (int ascii = 97; ascii <= 122; ++ascii)
    {
        //character will be a-z
        std::string character(1, char(ascii));


        for(unsigned int i = 0; i < wrongWord_.size(); ++i) {
            modWord = wrongWord_;
            modWord.replace(i,1 , character);

            if (isWord(modWord)){
                suggestions.push_back(modWord);
            }
        }
    }
}

void SpellChecker::
checkSwappedWithNeighbor(std::string &wrongWord_, std::vector<std::string> &suggestions) {
    for (unsigned int i = 0; i < wrongWord_.size()-1; ++i) {
        std::swap(wrongWord_[i], wrongWord_[i+1]);
        if (isWord(wrongWord_)){
            suggestions.push_back(wrongWord_);
        }

        //swap back so for followign swap
        std::swap(wrongWord_[i], wrongWord_[i+1]);
    }
}


//returns vector of incorrect words
std::vector<std::string> SpellChecker::incorrectWords() {
    std::vector<std::string> wrongWords;

    for (unsigned int i = 0; i < wordsInText.size(); ++i){

        //if not in the dictionary than it is a mispelled word
        if(!isWord(wordsInText.at(i))){
            wrongWords.push_back(wordsInText.at(i));
        }
    }

    return wrongWords;
}

void SpellChecker:: printDict() {
    for(auto word : hashDict) {
        std::cout<< word << std::endl;
    }
}

#endif

//Israel Meza
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include <ctime>

#include "SpellChecker.h"
#include "SetSpellChecker.h"

// using namespace std;

template<typename T>
void print(T type){
    std::cout << type << std::endl;
}

int main(int argc, char const *argv[])
{
    std::string check_it_file = argv[1];
    std::string dictionaryFile = argv[2];

    SpellChecker hashChecker(check_it_file, dictionaryFile);
    SetSpellChecker setSpellChecker(check_it_file, dictionaryFile);

     std::ofstream ofs ("time-results.txt", std::ofstream::out);


    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    hashChecker.checkSpelling();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    ofs << "hash time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    
    start = std::chrono::steady_clock::now();
    setSpellChecker.checkSpelling();
    end = std::chrono::steady_clock::now();
    ofs << "AVL time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    ofs.close();


    return 0;
}
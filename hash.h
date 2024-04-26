#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
  HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
  MyStringHash(bool debug = true)
  {
    //I took out the generateRValues() func because the guide
    //presented a different way to generate 5 random numbers
    if(false == debug){
      srand(std::time(0)); 
      for(int i = 0; i < 5; i++){
        rValues[i] = rand(); 
      }
    }
  }
  // hash function entry point (i.e. this is h(k))
  HASH_INDEX_T operator()(const std::string& k) const{
    // Add your code here
    std::vector<unsigned long long> decimal(5, 0);
    std::vector<unsigned long long> powersOf36(6);
    for(int i = 0; i < 6; i++){
      powersOf36[i] = std::pow(36, 5 - i);  
    }
    int repetitions = k.size() / 6;
    int repsIn = 0;
    while(repetitions != 0){
      int startpos = k.size() - (6 * repsIn) - 1;
      std::vector<HASH_INDEX_T> bitInt;
      for(int start = startpos; start > startpos - 6; start--){
        bitInt.push_back(letterDigitToNumber(k.at(start)));
      }
      unsigned long long basehash = 0;
      for(size_t i = 0; i < bitInt.size(); i++){
        basehash += powersOf36[i] * bitInt.at(5 - i);
      }

      decimal.at(4 - repsIn) = basehash;
      repsIn++;
      repetitions--;
    }
    int remainder = k.size() % 6;
    if(remainder != 0){
      std::vector<HASH_INDEX_T> bitInt(6, 0);
      int i = 0;
      for(int s = remainder - 1; s >= 0; s--){
        bitInt.at(5 - i) = letterDigitToNumber(k.at(s));
        i++;
      }
      unsigned long long basehash = 0;
      for(size_t i = 0; i < bitInt.size(); i++){
        basehash += (powersOf36[i] * bitInt.at(i));
      }
      decimal.at(4 - repsIn) = basehash;
    }
    HASH_INDEX_T hashnumber = 0;
    for(int i = 0; i < 5; i++){
      hashnumber += (decimal[i] * rValues[i]);
    }
    return hashnumber;
  }

  // A likely helper function is to convert a-z,0-9 to an integral value 0-35
  HASH_INDEX_T letterDigitToNumber(char letter) const
  {
      // Add code here or delete this helper function if you do not want it
    char convertedletter = tolower(letter);
    HASH_INDEX_T hashnumber = static_cast<HASH_INDEX_T>(convertedletter);
    if(hashnumber > 47 && hashnumber < 58){
      hashnumber -= 22;
    }
    else{
      hashnumber -= 97;
    }
    return hashnumber;
  }
};
#endif
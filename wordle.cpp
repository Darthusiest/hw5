#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recursive(size_t pos, std::string curr, std::string floating, const std::set<std::string>& dict, std::set<std::string>& answer, const std::string& in); //recursive helper

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    size_t pos = 0; 

    std::set<std::string> answer;
    std::string curr = in;

    //recursive helper
    //position, current word, floating letters that are unused, dict, answer set, original in 
    recursive(pos, curr, floating, dict, answer, in);
    return answer;
}

// Define any helper functions here
void recursive(
    size_t pos, 
    std::string curr, 
    std::string floating, 
    const std::set<std::string>& dict, 
    std::set<std::string>& answer,
    const std::string& in)
{
    //base case
    if(pos == in.size()){ //all floating letters have been placed
        if(floating.empty() && dict.find(curr) != dict.end()){
            //append curr into answer
            answer.insert(curr);
        }
        return; 
    }

    if(in[pos] != '-'){
        //force position to match fixed pattern 
        curr[pos] = in[pos];

        //recursive call to move to next position
        recursive(pos + 1, curr, floating, dict, answer, in);
        return; 
    }

    if(in[pos] == '-'){
        //try every letter 


        for(char c = 'a'; c <= 'z'; ++c){
            curr[pos] = c;
            std::string nxt_floating = floating;

            for(size_t i = 0; i < nxt_floating.size(); ++i){
                if(nxt_floating[i] == c){
                    //erase 
                    nxt_floating.erase(i, 1);
                    break;
                }
            }
            recursive(pos + 1, curr, nxt_floating, dict, answer, in);
        }
    }

}
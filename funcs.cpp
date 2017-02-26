#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "funcs.hpp"

bool isNumber(std::string s){
    // There should only be one decimal point
    bool seenDec = false;

    for (auto i : s){
        if( i == '.' && !seenDec ){
            seenDec = true;
            continue;
        }
        if( !std::isdigit(i) ){
            return false;
        }
    }

    return true;
}

// Display the vector in a readable way. If not the main vector, we should use a different "theme?"
void dispVec ( const std::vector<double> &input, bool mainVec){
    if(mainVec){
        std::cout << "[ ";
    }
    else {
        std::cout << "> ";
    }

    // No line should contain more than 10 numbers...
    int newler = 0;

    // Display every entry, one at a time
    for( auto i : input ){
        if((newler % 10 == 0) && (newler != 0)){
            std::cout << std::endl << "* "; 
        }
        std::cout << i << " ";
        newler++;
    }

    if(mainVec){
        std::cout << "]";
    }

    std::cout << std::endl;
}

// Handle all of the operations
std::vector<double> process ( const std::vector<double> &input, unsigned short command ){

    // A vector for our result(s)
    std::vector<double> res {};
    
    // NOTE: Don't include the nochange flag
    switch(command & ~comms::NOCHANGE){
        // Add function (get the sum of every number)
        case 1: {
            double temp = 0; 

            for( auto i : input ){
                temp += i; 
            }

            // Add it to the end and quit. This will be done alot
            res.push_back(temp);
            break; 
        }
        // Multiplication functions (product or * too)
        case 2: {
            double temp = 1;
        
            for( auto i: input ){
                temp *= i;
            }

            // Add it to the new away.
            res.push_back(temp);
            break;
        }
        // Average (or mean) function
        case 3: {
            double temp = 0;

            for( auto i : input ){
                temp += i;
            }

            temp /= input.size();

            res.push_back(temp);

            break;
        }

        // This shouldn't be called unless there is some issue matching commands
        default: {
            res = input;
            std::cout << "Command not found" << std::endl;

            // If this was called with a nonzero command, there is definately an issue
            if( command ){
                std::cout << "Please report that the command " << command << " might be broken." << std::endl;
            }
        }
    }

    return res;
}

// If the command ends with a '_' then we shouldn't change the vector.
bool isNoChange ( std::string &input ){
    if(input[input.length() - 1] == '_'){
        input = input.substr(0, input.length() - 1);
        return true; 
    }

    return false;

}

void toLowerCase(std::string &input){
    for( auto &i : input){
        i = tolower(i); 
    }
}

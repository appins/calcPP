#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "funcs.hpp"

bool isNumber(std::string s){
    // There should only be one decimal point
    bool seenDec = false;

    bool canBeMinus = true;

    for (auto i : s){
        if( i == '-' && canBeMinus ){
            canBeMinus = false;
            continue;
        }
        if( i == '.' && !seenDec ){
            seenDec = true;
            continue;
        }
        if( !std::isdigit(i) ){
            return false;
        }
        canBeMinus = false;
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

            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            double temp = 0;

            for( auto i : input ){
                temp += i;
            }

            temp /= input.size();

            res.push_back(temp);

            break;
        }

        // Clear the array. We don't actually have to do anyting here, which is nice
        case 4: {
            break;
        }

        // Delete a single element from the end
        case 5: {
            res = input; 

            if(res.size() > 0){
                res.pop_back();
            }

            break;
        } 
        
        // Get maximum value in the vector
        case 6: {
            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            // We shouldn't start with zero just incase the array is all negative
            auto temp = input[0];

            for( auto i : input ){
                if( i > temp ){
                    temp = i;
                }
            }

            res.push_back(temp);

            break;
        }

        // Get the minimum value
        case 7: {
            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            // We shouldn't start with zero incase the numbers are all over zero
            auto temp = input[0];

            for( auto i : input ){
                if( i < temp ){
                    temp = i;
                }
            }

            res.push_back(temp);

            break;
        }

        // Move the oldest value to the newest value, do this by cycling
        case 8: {
            bool once = true;
            auto endof = input[0];

            for(auto i : input){
                if(once){
                    once = false;
                    continue;
                }
                res.push_back(i);
            }

            res.push_back(endof);

            break;
        }

        // Move the newest value to the oldest value
        case 9: {
            // Push back the oldest value first
            res.push_back(input[input.size() - 1]);

            for(int i = 0; i < input.size() - 1; i++){
                res.push_back(input[i]);
            }

            break;
        }

        // This shouldn't be called unless there is some issue matching commands
        default: {
            res = input;
            std::cout << "Command not found" << std::endl;

            // If this was called with a nonzero command, there is most likley an issue
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

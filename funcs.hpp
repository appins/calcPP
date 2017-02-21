#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

// A namespace for commands
namespace comms {
    const unsigned char ADD = 1;
    const unsigned char MUL = 2;

    // If the input shouldn't be changed, this will be set
    // This means, most of the time, they put a _ on the end of the comamnd
    const unsigned char NOCHANGE = 0x80;
}

bool isNumber(std::string s){
    for (auto i : s){
        if( !std::isdigit(i) ){
            return false;
        }
    }

    return true;
}

// Display the vector in a readable way. If not the main vector, we should use a different "theme?"
void dispVec ( const std::vector<double> &input, bool mainVec = true ){
    if(mainVec){
        std::cout << "[ ";
    }
    else {
        std::cout << "> ";
    }

    // No line should contain more than 5 numbers...
    int newler = 0;

    // Display every entry, one at a time
    for( auto i : input ){
        std::cout << i << " "; 
        if(newler % 5 == 0 && newler != 0){
            
        }
        newler++;
    }

    if(mainVec){
        std::cout << "]";
    }

    std::cout << std::endl;
}

std::vector<double> process ( const std::vector<double> &input, unsigned char command ){

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

        // This shouldn't be called unless there is some issue with corr
        default: {
            std::cout << "Command not found" << std::endl;
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

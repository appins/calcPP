#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "funcs.hpp"

using namespace std;

int main(){
    // Map all the commands to integers
    // An attemp should be made to make, at least the basic functions, work with just the numberpad
    map<string, unsigned short> corr = {
        // Words to be reconized as addition operators
        {"add", comms::ADD},
        {"sum", comms::ADD},
        {"+"  , comms::ADD},
        // Words to be reconized as multiplication operators
        {"mul",      comms::MUL},
        {"product",  comms::MUL},
        {"*",        comms::MUL},
        {"multiply", comms::MUL},
        // Words to be reconized as mean operators (Average)
        {"mean",    comms::MEAN},
        {"+/",      comms::MEAN},
        {"average", comms::MEAN},
        // Words to be reconized as clear operators
        {"clear", comms::CLEAR},
        {"clr",   comms::CLEAR},
        {"=0",    comms::CLEAR},
        // Delete operators
        {"delte", comms::DEL},
        {"del"  , comms::DEL},
        {"--1", comms::DEL}

    };

    // Not technically a stack, but hey. Vector for holding all the variable
    vector<double> nstack = {};

    cout << "[ Oldest >> Newest ]" << endl;
     
    // Loop until the user wants to exit
    while (true){
        cout << ":";
        string input;
        getline(cin, input);

        if(input == "exit"){
            cout << "Bye!" << endl;
            break;
        }

        if (input == ""){
            cout << "Please enter a number or command" << endl;    
        }
        else if(isNumber(input)){
            nstack.push_back(std::stod(input));
        }
        
        else {
            // Put input into lower case
            toLowerCase(input);

            unsigned short noChange = isNoChange(input) << 7;
            int lookup = corr[input] | noChange;

            // This checks if there is an error beforehand. If you don't have this, it will always overwrite the entire vector
            if( lookup == noChange ){
                cout << "Command not found" << endl;
            }
            else {
                // If we have nochange set, we shouldn't overwrite our vector. We should just display the change
               if( lookup & comms::NOCHANGE){
                   dispVec(process(nstack, lookup), false);
               }
               else {
                   nstack = process(nstack, lookup); 
               }
            }
        }

        dispVec(nstack);

    }

    return 0;
}

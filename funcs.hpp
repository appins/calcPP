#ifndef funcs_calcpp

#define funcs_calcpp

// A namespace for commands
namespace comms {
    const unsigned char ADD = 1;
    const unsigned char MUL = 2;

    // If the input shouldn't be changed, this will be set
    // This means, most of the time, they put a _ on the end of the comamnd
    const unsigned char NOCHANGE = 0x80;
}

bool isNumber(std::string s);
    
// Display the vector in a readable way. If not the main vector, we should use a different "theme?"
void dispVec ( const std::vector<double> &input, bool mainVec = true );
// Handle all of the operations
std::vector<double> process ( const std::vector<double> &input, unsigned char command );
// If the command ends with a '_' then we shouldn't change the vector.
bool isNoChange ( std::string &input );
void toLowerCase(std::string &input);

#endif

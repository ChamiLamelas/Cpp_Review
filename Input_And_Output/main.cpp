#include <iostream>
#include <string>

int main() {
    // Different types of output streams
    std::cout << "cout message" << std::endl;
    std::cerr << "cerr message" << std::endl;
    std::clog << "clog message" << std::endl;

    // Reading in 1 input (integer)
    int input;
    std::cout << "enter input: ";
    std::cin >> input;
    std::cout << "input = " << input << std::endl;

    // Reading in 2 inputs separated by whitespace (chaining stream operator for std::cin)
    int input1, input2;
    std::cout << "enter input1 and input2 separated by whitespace: ";
    std::cin >> input1 >> input2;
    std::cout << "input1 = " << input1 << " input2 = " << input2 << std::endl;

    // Reading in an input with a space (std::string is the string type from <string>)
    std::cout << "enter string input (can include spaces): ";

    /*
    A couple notes: 

    - std::string is mutable unlike Java String (as it supports a push_back function, see documentation
    for getline: https://cplusplus.com/reference/string/string/getline/)
    - However, string literals are immutable because they are const char arrays (see this dicussion:
    https://stackoverflow.com/questions/2245664/what-is-the-type-of-string-literals-in-c-and-c)
    - getline fails to work following previous calls to cin because cin with << does not consume
    newlines while getline does so use cin.ignore() to clear the newline otherwise getline will read
    nothing (calling it with no arguments extracts 1 character, but it also extracts up to and including
    a delimiter character, see initials example here: https://cplusplus.com/reference/istream/istream/ignore/)
    */
    std::string string_input;
    std::cin.ignore();
    std::getline(std::cin, string_input);
    std::cout << "string input = " << string_input << std::endl;
}

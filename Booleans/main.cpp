#include <iostream>

int main()
{
    std::cout << "sizeof(bool) = " << sizeof(bool) << std::endl;

    // Can also set to 1 and 0
    bool true_var{true};
    bool false_var{false};

    // By default cout displays booleans as 1s and 0s
    std::cout << "true_var = " << true_var << std::endl;
    std::cout << "false_var = " << false_var << std::endl;

    // Sending boolalpha into cout tells it to display them as true and false
    // Also noboolalpha: https://en.cppreference.com/w/cpp/io/manip/boolalpha
    std::cout << std::boolalpha;
    std::cout << "true_var = " << true_var << std::endl;
    std::cout << "false_var = " << false_var << std::endl;

    // Make sure to surround boolean expressions in () when printing them - otherwise it won't compile
    std::cout << (true_var == false_var) << std::endl;

    
}
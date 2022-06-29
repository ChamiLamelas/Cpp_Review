#include <iostream>

int main()
{
    std::cout << "sizeof(char) = " << sizeof(char) << std::endl;

    // Can initialize characters from character literals or from integer literals (0-255 ASCII)
    char a{'a'};
    std::cout << "a = " << a << std::endl;
    char a_from_num{97};
    std::cout << "a_from_num = " << a_from_num << std::endl;

    // Can get numerical value from char: https://stackoverflow.com/a/5030541 (don't think casting is necessary)
    int ia = a;
    std::cout << "ia = " << ia << std::endl;
}
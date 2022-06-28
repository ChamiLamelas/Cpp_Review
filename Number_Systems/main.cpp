#include <iostream>

int main()
{
    /*
    To indicate that we will be specifying the value to be stored in number1 using base 10, just enter
    the base 10 value as normal. To indicate that we will be specifying the value to be stored in
    number2 using base 8, prefix the octal number with a 0. To indicate that we will be specifying
    the value to be stored in number3 using base 16, prefix the hexadecimal number with a 0x. To
    indicate that we will be specifying the value to be stored in number4 using base 2, prefix the
    binary number with a 0b.

    Regardless of the number system used to specify the values stored in these variables, their value
    will be displayed in base 10.
    */
    int number1 = 15;
    int number2 = 017;
    int number3 = 0x0F;
    int number4 = 0b00001111;

    /*
    Found out the std::endl is not just '\n', in fact it also triggers a stream flush of std::cout. See 
    here: https://stackoverflow.com/questions/7324843/why-use-endl-when-i-can-use-a-newline-character

    Also: https://www.quora.com/What-does-it-mean-to-flush-the-output-stream-in-C++

    Note (see comments of first link) that adding a '\n' will trigger some automatic substitution (upon
    display/write to std::cout I assume) of the system-appropriate endline character.

    Thus, it may be more appropriate to use 3 '\n' here instead of the 4 std::endl.
    */
    std::cout << "number1 = " << number1 << std::endl
              << "number2 = " << number2 << std::endl
              << "number3 = " << number3 << std::endl
              << "number4 = " << number4 << std::endl;
}
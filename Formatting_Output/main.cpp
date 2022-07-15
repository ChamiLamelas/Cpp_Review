#include <iostream>
#include <iomanip>
#include <ios>
#include <bitset>

/*
Additional Input/Output headers:

https://en.cppreference.com/w/cpp/header/iostream
https://en.cppreference.com/w/cpp/header/iomanip
https://en.cppreference.com/w/cpp/header/ios

Bitset for printing in binary (I/O headers only provide support for bases 8, 10, and 16)
https://en.cppreference.com/w/cpp/utility/bitset
*/

int main()
{
    /*
    This mimics the behavior of just sending std::endl - flush forces all the contents of the output buffer
    to be displayed on the screen.
    */
    std::cout << "hello\n"
              << std::flush;

    // Making unformatted table
    std::cout << "Name Age\nBob 1\nChris 2\nJoe 3" << std::endl;

    /*
    Making formatted table - all right justified (default justification).

    Note that if \n is included in the same string literal as Age it appears to insert a space into that field making Age appear
    one space to the left of what it should be (i.e. the numbers in the following rows no longer appear under e in Age but one space
    to the right of it). I could not find anything online to confirm this but it seems that the \n (or more specifically ASCII char 13)
    appears to be included in the 10 character field. If \n is sent to the stream after as its own literal, everything is okay. Also,
    the misalignment can be further seen by printing 20 dashes above the table and seeing that if \n is put in the same literal as Age
    that e in Age is at the 19th character position when it should be at the 20th character position as it is the last character in the
    2nd 10 character field.

    The C++ documentation for setw is quite poor, here are some links:

    1. https://en.cppreference.com/w/cpp/io/manip/setw
    2. https://cplusplus.com/reference/iomanip/setw/
    3. https://www.simplilearn.com/tutorials/cpp-tutorial/setw-cpp
    4. https://www.delftstack.com/howto/cpp/setw-in-cpp/

    Link 2 refers to setw setting the field width without explaining what it means.
    Links 3 and 4 indicates that field width may mean the minimum number of characters the next piece of data passed
    to cout will take up. Note that if we pass in a string longer than n for setw(n) that it is still entirely printed.

    Note link 1 (scroll down) that << will reset the width by calling setw(0). This can be seen by running:

    std::cout << std::left << std::setw(10) << "abc" << "d" << "e" << std::endl;
    */
    std::cout << std::setw(10) << "Name" << std::setw(10) << "Age"
              << "\n"
              << std::setw(10) << "Bob" << std::setw(10) << 1
              << "\n"
              << std::setw(10) << "Chris" << std::setw(10) << 2
              << "\n"
              << std::setw(10) << "Joe" << std::setw(10) << 3 << std::endl;

    // Making formatted table - all left justified
    std::cout << std::left;
    std::cout << std::setw(10) << "Name" << std::setw(10) << "Age"
              << "\n"
              << std::setw(10) << "Bob" << std::setw(10) << 1
              << "\n"
              << std::setw(10) << "Chris" << std::setw(10) << 2
              << "\n"
              << std::setw(10) << "Joe" << std::setw(10) << 3 << std::endl;

    // Making formatted table - mixed justification (names, column headers left justified, ages right justified)
    std::cout << std::left << std::setw(10) << "Name" << std::setw(10) << "Age"
              << "\n"
              << std::setw(10) << "Bob" << std::right << std::setw(10) << 1
              << "\n"
              << std::left << std::setw(10) << "Chris" << std::right << std::setw(10) << 2
              << "\n"
              << std::left << std::setw(10) << "Joe" << std::right << std::setw(10) << 3 << std::endl;

    // Making formatted table - internal justification (sign of transaction amount on left, value of transaction amount on right)
    std::cout << std::left << std::setw(15) << "Transaction" << std::setw(10) << "Amount"
              << "\n"
              << std::setw(15) << "Payroll" << std::internal << std::setw(10) << 100
              << "\n"
              << std::left << std::setw(15) << "Tax" << std::internal << std::setw(10) << -200
              << "\n"
              << std::left << std::setw(15) << "Birthday" << std::internal << std::setw(10) << 300 << std::endl;

    // Making formatted table - all right justification with - fill character (default is space)
    std::cout << std::setfill('-');
    std::cout << std::setw(10) << "Name" << std::setw(10) << "Age"
              << "\n"
              << std::setw(10) << "Bob" << std::setw(10) << 1
              << "\n"
              << std::setw(10) << "Chris" << std::setw(10) << 2
              << "\n"
              << std::setw(10) << "Joe" << std::setw(10) << 3 << std::endl;
    std::cout << std::setfill(' '); // Resetting for next demos

    // Making formatted table - internal justification with positive sign shown for nonnegative numbers
    std::cout << std::showpos << std::left << std::setw(15) << "Transaction" << std::setw(10) << "Amount"
              << "\n"
              << std::setw(15) << "Payroll" << std::internal << std::setw(10) << 100
              << "\n"
              << std::left << std::setw(15) << "Tax" << std::internal << std::setw(10) << -200
              << "\n"
              << std::left << std::setw(15) << "Test" << std::internal << std::setw(10) << 0 << std::endl;
    std::cout << std::noshowpos; // Resetting for next demos

    /*
    Printing 12 in various bases. Using bitset for printing in base 2 as recommended here: https://stackoverflow.com/a/7349767

    Note, std::dec, oct, and hex have no effect on printing decimal numbers
    */
    std::cout << std::dec << 12 << "\n"
              << std::oct << 12 << "\n"
              << std::hex << 12 << "\n"
              << std::bitset<8>(12) << std::endl;

    // Can also have the base shown when printing in various bases (dec there is no base, doesn't apply to bitset)
    std::cout << std::showbase << std::oct << 12 << "\n"
              << std::hex << 12 << std::endl;

    std::cout << std::dec << std::noshowbase; // Resetting for next demos

    // Have hex digits and e in scientific notation be uppercase
    std::cout << std::uppercase;
    std::cout << std::hex << 12 << "\n"
              << 1e10 << std::endl;
    std::cout << std::dec << std::nouppercase; // Resetting for next demos

    /*
    Can force integer numbers stored in floating point types to be shown with a decimal. Note enough 0s are appended in order to
    satisfy the currently set precision with std::precision: https://cplusplus.com/reference/ios/showpoint/
    */
    std::cout << 1.0 << "\n" << std::showpoint << 1.0 << std::endl;

    /*
    Show floating point numbers in fixed format (i.e. with number of decimals specified by std::precision which has default 6)
    See here: https://cplusplus.com/reference/ios/fixed/
    */
    std::cout << std::fixed;
    std::cout << 3.141592653589 << "\n"
              << 2006.0 << "\n"
              << 1.34e-10 << std::endl;

    /*
    Can also show in scientific notation always (by default this will be used where necessary to most accurately represent the number)
    Scientific notation is defined as 1 digit before decimal point and then a number of decimals specified by std::precision as above
    */
    std::cout << std::scientific;
    std::cout << 3.141592653589 << "\n"
              << 2006.0 << "\n"
              << 1.34e-10 << std::endl;
    return 0;
}
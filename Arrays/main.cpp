#include <iostream>

int main()
{
    /*
    This is known as a C-style array and does not support a length() operation.
    This is not std::array which is something else that seems more akin to a Java array (e.g. size aware), see here:
    https://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array

    These arrays are initialized to garbage (no guarantee to be 0 for ints say)
    */

    int scores[10];
    for (auto i{0}; i < 10; i++)
    {
        std::cout << scores[i] << " ";
    }
    std::cout << std::endl;

    // Can initialize with contents, const specifies it cannot be edited (compile error).
    const int ages[]{1, 2, 3};

    // Can also supply a size when giving an array literal, any left over spots are filled with default value of array type
    int counts[5]{10, 5};
    for (auto i{0}; i < 5; i++)
    {
        std::cout << counts[i] << " ";
    }
    std::cout << std::endl;

    // Can use range-based loop over arrays:
    for (auto e : counts)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // Calculating the size (pre C++ 17)
    std::cout << sizeof(counts) / sizeof(counts[0]) << std::endl;

    // Calculating the size (since C++ 17)
    std::cout << std::size(counts) << std::endl;

    // Initializing a char array with a C-style string - must terminate with null character \0
    char c_str[]{'h', 'e', 'l', 'l', 'o', '\0'};
    char c_str_wrong[]{'h', 'e', 'l', 'l', 'o'};

    // Note that without a null character, there is no guarantee on what is printed after the truth string
    std::cout << c_str << std::endl;
    std::cout << c_str_wrong << std::endl;

    /*
    Can also initialize character arrays with string literals. This is because string literals are really (const)
    character arrays with the null character implicitly added (see print). https://cplusplus.com/doc/tutorial/ntcs/

    At first, I wondered why "hello" can be put into a char[] not a const char[] (as it's an array of 6 const char
    see here: https://stackoverflow.com/questions/15508148/what-is-the-type-of-a-string-literal-in-c). 

    It turns out the contents of const char[] hello are put into char[] when you do char x[] = "hello" versus assigning
    a non const pointer to the same location to a const pointer: 
    https://stackoverflow.com/questions/7564033/difference-between-char-and-char
    */
    char c_str_literal[]{"hello"};
    std::cout << std::size(c_str_literal) << " " << c_str_literal << std::endl;

    // Note character arrays are the only type of array that can be printed by default (prints gibberish)
    std::cout << counts << std::endl;

    // C++ allows you to index beyond array bounds (can give garbage or crash due to restricted memory protection from OS)
    std::cout << counts[5] << " " << counts[-1] << std::endl;

    return 0;
}
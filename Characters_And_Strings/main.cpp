#include <iostream>

// Character utility library: https://en.cppreference.com/w/cpp/header/cctype (automatically included on GCC)
#include <cctype>

// C-string manipulation library: https://cplusplus.com/reference/cstring/
#include <cstring>

// Class string: https://cplusplus.com/reference/string/string/
#include <string>

// Read only string class: see below
#include <string_view>

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

    /*
    alnum for checking if alphanumeric - returns nonzero number if it is (treat like true),
    0 if its not (treat like false)

    Other functions also included below (see documentation for details) work like isalnum
    */
    std::cout << std::isalnum(a) << " " << std::isalnum('^') << std::endl;
    std::cout << std::isalpha(a) << " " << std::isalpha('9') << std::endl;
    std::cout << std::isblank(' ') << " " << std::isblank('\n') << std::endl;
    std::cout << std::isdigit(a) << " " << std::isdigit('9') << std::endl;
    std::cout << std::islower(a) << " " << std::isupper(a) << std::endl;

    /*
    This raises warnings due to narrowing conversion of int to char. Use static cast to convert
    int to char as recommended here: https://stackoverflow.com/a/16899648

    Docs on static_cast: https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=msvc-170
    */
    char upper_b{static_cast<char>(std::toupper('b'))};
    char lower_b{static_cast<char>(std::tolower('B'))};

    std::cout << lower_b << " " << upper_b << std::endl;

    // Now to look at some functions of cstring
    const char *hello{"hello"};
    std::cout << std::strlen(hello) << std::endl;

    // strcmp operates like Java compareTo (also strncmp which compares up to n characters from the beginning)
    const char *yellow{"yellow"};
    std::cout << std::strcmp(hello, yellow) << std::endl;

    // character search returns substring (as const char*) starting with the first occurrence of the target character
    const char *result{strchr(hello, 'l')};
    std::cout << result << std::endl;

    // Target not in str -> get nullptr (exercise: implement function that counts occurrences of character in string)
    result = strchr(hello, 'y');
    std::cout << (result == nullptr) << std::endl;

    // Search reversed
    result = strrchr(hello, 'l');
    std::cout << result << std::endl;

    /*
    Could alternatively use pointers for strcat, strcpy (some functions deem these unsafe
    b/c destination could be too small)
    */

    char dest[50]{"Hello"};
    char source[]{" World"};

    std::strcat(dest, source);
    std::cout << dest << std::endl;

    char source2[]{"Hello"};
    char dest2[std::strlen(source2)];

    // Also strncpy
    std::strcpy(dest2, source2);
    std::cout << dest2 << std::endl;

    // Makes empty string (note here and below std::string automatically prints properly)
    std::string empty_str;
    std::cout << empty_str << std::endl;

    // Initializes string with literal (i.e. a c-string char[] / char*)
    std::string literal_str{"Hello"};
    std::cout << literal_str << std::endl;

    // Initializes string from another string
    std::string copy_str{literal_str};
    std::cout << copy_str << std::endl;

    // Initializes part of string
    std::string part_str{"Hello", 2};
    std::cout << part_str << std::endl;

    // Initializes string with repeated characters
    /*
    std::string repeated_str{3, 'a'} will trigger the initializer_list constructor which works
    with a list of characters (shown below) see here: https://stackoverflow.com/a/38919147
    */
    std::string repeated_str(3, 'a');
    std::cout << repeated_str << std::endl;

    // Initializes string from substring specified by another string, start, and length
    std::string substr_str{literal_str, 2, 2};
    std::cout << substr_str << std::endl;

    // Initializer list (https://cplusplus.com/reference/string/string/string/)
    std::string chr_arr_str{'H', 'e', 'l', 'l', 'o'};
    std::cout << chr_arr_str << std::endl;

    /*
    Strings can be assigned to something else in a variety of ways
    (https://cplusplus.com/reference/string/string/operator=/)
    */
    chr_arr_str = "Hello World";
    std::cout << chr_arr_str << std::endl;

    /*
    In the video, he says that using a raw pointer with a string literal (const char *)
    is worse because space is leftover. However, this does not seem entirely true as the
    implementation of string literals in C++ is hidden (see:
    https://stackoverflow.com/a/9504612 which discusses also how these pointers should
    not be freed upon reassignment as they weren't necessarily on the heap).

    However, he is correct that any memory that is heap allocated used by std::string is
    cleaned up in reassignment: https://stackoverflow.com/a/3601514
    */

    /*
    In his video on overloading functions, he brings up a string_view (documentation:
    https://en.cppreference.com/w/cpp/string/basic_string_view) but doesn't explain
    what it is really. A string_view is a special type that represents a read only view of
    a string that is owned elsewhere (see here on what ownership means in programming:
    https://stackoverflow.com/a/49025071).

    The purpose of string_view is to provide a more efficient way to pass around string
    data that only has to be read. It allows for a variety of non modification operations
    (see documentation).

    They can be initialized from string literals as well as string objects (because string
    supports an implicit conversion to a string_view see
    https://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view and
    https://en.cppreference.com/w/cpp/string/basic_string/operator_basic_string_view).

    On a related note, one is able to implement implicit conversion operators for custom types:
    https://en.cppreference.com/w/cpp/language/cast_operator

    Another thing that came up in constexpr, which is used to mark an expression (variable, function,
    etc.) as able to be evaluated at compile time (see here:
    https://en.cppreference.com/w/cpp/language/constant_expression).

    For more about string_view such as conversions from string_view to string, see here:
    https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/

    Another question is: why use string_view over const string&? See below link (big one is O(1) substr):
    https://stackoverflow.com/questions/40127965/how-exactly-is-stdstring-view-faster-than-const-stdstring

    One thing that I am not entirely sure about (perhaps this is just a defintion) is why, if a string_view
    is implemented as a char * and a size, does it not support a [] operator that allows character modification
    of its contents (not growing).
    */

    std::string s{"hello"};
    std::string_view sv{s};
    std::string_view ssv{sv.substr(0, 2)};
    std::cout << s << " " << sv << " " << ssv << std::endl;
    s[0] = 'j';
    std::cout << s << " " << sv << " " << ssv << std::endl;

    return 0;
}
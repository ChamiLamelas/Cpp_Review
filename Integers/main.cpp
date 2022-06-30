#include <iostream>
#include <limits>

int main()
{
    // Using {} is called braced initialization, () is called functional, = is called assignment

    // Can yield garbage: https://stackoverflow.com/questions/19665876/why-do-i-need-to-initialize-an-int-variable-to-0
    // Some compilers yield 0, but bad practice
    int uninitialized;
    std::cout << "unitialized =" << uninitialized << std::endl;

    // Initializes to 0
    int init_empty{};
    std::cout << "init_empty =" << init_empty << std::endl;

    // Initializes to 1
    int init_value{1};
    std::cout << "init_value =" << init_value << std::endl;

    // This will trigger a compile error because 1.2 cannot be converted to an integer type.
    // int init_real{1.2};

    // These will both silently truncate 1.2 to 1
    int functional_init_real(1.2);
    std::cout << "functional_init_real = " << functional_init_real << std::endl;
    int assignment_init_real = 1.2;
    std::cout << "assignment_init_real = " << assignment_init_real << std::endl;

    // sizeof is an operator that can be given a data type to get its size in bytes or can be given
    // a variable to get the number of bytes allocated to it
    std::cout << "sizeof(int) = " << sizeof(int) << "\nsizeof(init_value) = " << sizeof(init_value) << std::endl;

    /*
    Observe some of these types are redundant, see:
    https://stackoverflow.com/questions/18971732/what-is-the-difference-between-long-long-long-long-int-and-long-long-i
    https://en.cppreference.com/w/cpp/language/types
    */
    std::cout << "sizeof(short) = " << sizeof(short) << std::endl;
    std::cout << "sizeof(short int) = " << sizeof(short int) << std::endl;
    std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
    std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
    std::cout << "sizeof(long int) = " << sizeof(long int) << std::endl;
    std::cout << "sizeof(long long) = " << sizeof(long long) << std::endl;
    std::cout << "sizeof(long long int) = " << sizeof(long long int) << std::endl;

    // Can get limits of integer types (only 3 listed here for simplicity, for more capabilities beyond min, max: https://en.cppreference.com/w/cpp/types/numeric_limits)
    std::cout << "min(int) = " << std::numeric_limits<int>::min() << "\nmax(int) = " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "min(short) = " << std::numeric_limits<short>::min() << "\nmax(short) = " << std::numeric_limits<short>::max() << std::endl;
    std::cout << "min(unsigned int) = " << std::numeric_limits<unsigned int>::min() << "\nmax(unsigned int) = " << std::numeric_limits<unsigned int>::max() << std::endl;

    /*
    C++ limits which integer types support arithmetic operations. In particular int (4 bytes) is the smallest integer type
    that supports these operations. Thus, when chars or shorts are added they are implicitly converted to int first and
    thus auto will deduce int because it sees a sum of 2 ints.
    */

    char char1{10};
    char char2{20};
    auto char_sum{char1 + char2};
    std::cout << "adding chars: " << sizeof(char1) << " -> " << sizeof(char_sum) << std::endl;

    short short1{10};
    short short2{20};
    auto short_sum{short1 + short2};
    std::cout << "adding shorts: " << sizeof(short1) << " -> " << sizeof(short_sum) << std::endl;

    /*
    size_t is the common size type and thus also used as a loop iterator, see here that it is an alias for some compiler
    determined unsigned integer type: https://cplusplus.com/reference/cstring/size_t/
    */
    size_t counter{0};
    std::cout << "sizeof(size_t) = " << sizeof(size_t) << std::endl;

    // Note that auto doesn't seem to infer size_t from a loop and instead just uses an integer (sizeof(x) = 4 while sizeof(size_t) = 8)
    for (auto x {0}; x < 10; x++)
    {
        if (x == 9)
        {
            std::cout << "sizeof(iterating variable) = " << sizeof(x) << std::endl;
        }
    }

    return 0;
}
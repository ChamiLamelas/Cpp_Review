#include <iostream>

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

    return 0;
}
#include <iostream>

int main()
{
    int data{0};

    /*
    Reference is essentially an alias of original. They must be declared to reference a particular
    variable and they cannot be changed to reference something else.
    */
    int &ref_data{data};

    // Reference and original have same value and are at same address (hence alias)
    std::cout << data << " " << ref_data << std::endl;
    std::cout << &data << " " << &ref_data << std::endl;

    // Changes using either original or reference is reflected in both
    data = 1;
    std::cout << data << " " << ref_data << std::endl;
    std::cout << &data << " " << &ref_data << std::endl;

    data = 2;
    std::cout << data << " " << ref_data << std::endl;
    std::cout << &data << " " << &ref_data << std::endl;

    // References act similar to const pointers
    int data2{2};
    int data3{3};

    // int* const is a constant pointer to an integer type (see https://stackoverflow.com/a/1143272)
    int *const data2_ptr{&data2};

    // With a const pointer to a (non-const) integer the data can be edited
    *data2_ptr = 4;
    std::cout << *data2_ptr << std::endl;

    // With a const pointer you can't change what it points to (compilation fails)
    // data2_ptr = &data3;

    // Can also make const references which is akin to a const pointer to const data
    const int &const_ref{data2};
    std::cout << const_ref << " " << data2 << std::endl;

    // Can still make changes to original variable
    data2 = 5;
    std::cout << const_ref << " " << data2 << std::endl;

    // Cannot change value using const reference (compilation failure)
    // const_ref = 6;

    const int *const const_data2_ptr{&data2};

    // Cannot change value or pointer using const pointer to const data (compilation failure)
    // const_data2_ptr = &data3;
    // *const_data2_ptr = 6;

    return 0;
}
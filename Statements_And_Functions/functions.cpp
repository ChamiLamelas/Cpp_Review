#include <iostream>
#include <string>

// Function definition
void PassByValue(int a)
{
    ++a;
    std::cout << "Inside PassByValue: a = " << a << " Address: " << &a << std::endl;
}

void PassByPointer(int *a_ptr)
{
    ++(*a_ptr);
    a_ptr = nullptr;
    std::cout << "Inside PassByPointer: a_ptr = " << a_ptr << " Address: " << (&a_ptr) << std::endl;
}

void PassByReference(int &a)
{
    ++a;
    std::cout << "Inside PassByReference: a = " << a << " Address: " << &a << std::endl;
}

int ReturnByValue()
{
    int result{3};
    std::cout << "Inside ReturnByValue: &result = " << &result << std::endl;
    return result;
}

std::string ReturnByValue2()
{
    std::string result { "Hello World" };
    std::cout << "Inside ReturnByValue2: &result = " << &result << std::endl;
    return result;
}
#include <iostream>
#include <exception>
#include <string>
#include <string_view>

struct StructA
{
    StructA() { std::cout << "StructA constructor" << std::endl; }
    ~StructA() { std::cout << "StructA destructor" << std::endl; }
};

struct StructB
{
    StructB() { std::cout << "StructB constructor" << std::endl; }
    ~StructB() { std::cout << "StructB destructor" << std::endl; }
};

void FuncB()
{
    std::cout << "In FuncB" << std::endl;
    StructA objA;
    StructB objB;
    std::cout << "About to throw up" << std::endl;
    // You can throw anything, just need catch with appropriate type - best to create custom exceptions inherit std::exception though
    throw "Throwing";
}

void FuncA()
{
    std::cout << "In FuncA" << std::endl;
    StructA objA;
    StructB objB;
    try
    {
        // If these were declared here, they would be destroyed before we see catch prints (as in Rao Lesson 28)
        // StructA objA;
        // StructB objB;
        FuncB();
        std::cout << "FuncA: returning to caller" << std::endl;
    }
    catch (const char *exp)
    {
        std::cout << "FuncA: Caught exception: " << exp << std::endl;
        std::cout << "Handled it" << std::endl;
    }
}

class CustomException : public std::exception
{
private:
    // To return char* with error message, must be associated with variable that lives beyond scope of what()
    std::string reason;

public:
    CustomException(std::string_view r) : reason(r) {}

    // throw() signifies that this function is expected to not throw an exception
    virtual const char *what() const throw()
    {
        return reason.c_str();
    }
};

int main()
{
    std::cout << "Main started" << std::endl;
    FuncA();
    std::cout << "Main ended" << std::endl;
    return 0;
}
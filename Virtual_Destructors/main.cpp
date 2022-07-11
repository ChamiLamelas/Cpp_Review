#include <iostream>

class Parent
{
public:
    ~Parent()
    {
        std::cout << "Parent destructor called" << std::endl;
    }
};

class Child : public Parent
{
public:
    ~Child()
    {
        std::cout << "Child destructor called" << std::endl;
    }
};

class Parent2
{
public:
    virtual ~Parent2()
    {
        std::cout << "Parent2 destructor called" << std::endl;
    }
};

class Child2 : public Parent2
{
public:
    ~Child2()
    {
        std::cout << "Child2 destructor called" << std::endl;
    }
};

int main()
{
    /*
    Note: only Parent destructor called. Why? static binding. Compiler sees
    Parent pointer, calls Parent destructor. Solution: make a Parent class
    with a virtual destructor.
    */
    Parent *ptr = new Child();
    delete ptr;

    Parent2 *ptr2 = new Child2();
    delete ptr2;

    return 0;
}
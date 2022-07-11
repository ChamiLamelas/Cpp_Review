#include <iostream>

/* 
1+ pure virtual member functions makes this an abstract class. An
interface can be modelled as an abstract class with all pure
virtual member functions and no member variables.

Note that you can inherit from multiple classes in C++ (different
from Java where you can inherit from multiple interfaces and only
1 class). This is not mentioned in the video but is in Lesson 10
of Rao.
*/
class Parent
{
public:
    // Pure virtual member function = abstract method
    virtual void Run() = 0;
};

class Child : public Parent
{
public:
    // Must override Run or this too will become abstract
    virtual void Run() override
    {
        std::cout << "Child run" << std::endl;
    }
};

int main()
{
    // Fails to compile
    // Parent p;

    Child c;
    c.Run();

    // This is still ok
    Parent *p{&c};
    p->Run();

    Parent &r{c};
    r.Run();

    // typeid gives us a way to see object at runtime (only use for debugging)
    std::cout << typeid(*p).name() << std::endl;
    std::cout << typeid(r).name() << std::endl;

    return 0;
}
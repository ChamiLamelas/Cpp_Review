#include <iostream>
#include <cmath>

// As of C++ 20, has PI: https://stackoverflow.com/a/49778493
#include <numbers>

#include "cylinder.h"
#include "dog.h"

class FirstCylinder
{
    /*
    Member variables are private by default, can only be variables or pointers (not references
    as it is common to leave them uninitialized which is impossible with references).

    structs and classes can be used interchangeably. The only difference is that by default
    struct members are public. structs are generally used to build small types with all public
    members (see here for supporting answer: https://stackoverflow.com/a/54596).

    sizeof(object) is the sum of sizeof(m) for each member m of the object. This may yield
    inaccurate results based on those members (e.g. sizeof of a pointer isn't really
    helpful, we really want the sizeof the data pointed to).
    */
public:
    double base_radius{1.0};
    double height{1.0};

public: // member functions aka methods
    // If no constructor is provided, compiler substitutes an empty constructor

    double volume()
    {
        return std::numbers::pi * std::pow(base_radius, 2) * height;
    }
};

class SecondCylinder
{
private:
    double base_radius;
    double height;

public:
    /*
    If this was removed, then the compiler will not generate an empty constructor
    if another constructor was provided (as below). Note, it is good practice to
    always provide a default constructor especially when a class is going to be
    used in an inheritance hierarchy because it will be called automatically
    if the class serves as the base for other classes

    Shorthand for telling the compiler to create an empty constructor is:

    SecondCylinder = default;
    */
    SecondCylinder()
    {
        base_radius = 1.0;
        height = 1.0;
    }

    SecondCylinder(double base_radius, double height)
    {
        // this is a pointer, this-> is equivalent to (*this).
        this->base_radius = base_radius;
        this->height = height;
    }

    double Volume()
    {
        return std::numbers::pi * std::pow(base_radius, 2) * height;
    }
};

Dog ReturnDog()
{
    Dog d("german shepherd", "bob", 1);
    return d;
}

void TakeDogByValue(Dog d) {}

int main()
{
    // Observe sizeof(s) == sizeof(s2) even though len(s2) > len(s)
    std::string s{"Hello"};
    std::cout << sizeof(s) << std::endl;
    std::string s2{"Hello world"};
    std::cout << sizeof(s2) << std::endl;

    FirstCylinder fc1;
    std::cout << fc1.volume() << std::endl;

    fc1.base_radius = 2.0;
    fc1.height = 2.0;

    std::cout << fc1.volume() << std::endl;

    SecondCylinder sc1;
    std::cout << sc1.Volume() << std::endl;

    SecondCylinder sc2(2.0, 2.0);
    std::cout << sc2.Volume() << std::endl;

    ThirdCylinder tc1;
    std::cout << tc1.GetBaseRadius() << " " << tc1.GetHeight() << " " << tc1.Volume() << std::endl;
    tc1.SetBaseRadius(2.0);
    tc1.SetHeight(2.0);
    std::cout << tc1.GetBaseRadius() << " " << tc1.GetHeight() << " " << tc1.Volume() << std::endl;

    // Allocates a ThirdCylinder on the heap (above examples all on stack)
    ThirdCylinder *tc2 = new ThirdCylinder();

    // Remember -> shortcut (for derefernece + member) for pointers (like with this)
    std::cout << tc2->Volume() << std::endl;

    delete tc2;

    /*
    This demo displays 5 prints.
    Print #1: Destructor is called on local objects returned from function (Dog object
    created and returned in ReturnDog), some compilers don't do this, GCC does.
    Print #2: Destructor is called on copy of object that is passed by value to a function
    when the function terminates (copy of d destroyed at end of TakeDogByValue).
    Print #3: Destructor is called when a Dog object is released via delete after being
    allocated on the heap (delete pd).
    Print #4-5: Destructor is called when a variable goes out of scope (d and d2 ho out of
    scope when main ends). Note that destructors are called in opposite order of constructors
    (d2 is destroyed first).
    */

    Dog d("golden retriever", "joe", 1);
    ReturnDog();
    TakeDogByValue(d);
    Dog *pd = new Dog("labrador retriever", "bob", 2);
    delete pd;
    Dog d2("bassett hound", "sebastian", 2);

    return 0;
}
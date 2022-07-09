#ifndef DOG_H
#define DOG_H

#include <string>
#include <string_view>

class Dog
{
private:
    std::string name;
    std::string breed;
    int *age;

public:
    Dog(std::string_view name, std::string_view breed, int age);
    /*
    Copy constructor, this was necessary for the destructor demo in main.cpp.
    The reason it is needed is the default copy constructor does a shallow
    copy where the pointer value is copied by TakeDogByValue. When the delete
    is done at the end of TakeDogByValue on the argument, it frees the memory
    (inadvertently) of the pointer in d in main as well. This causes a delete
    to be done on freed memory when d goes out of scope of main (triggering
    a crash). This is all discussed as the motivation for the copy
    constructor in lesson 9 of Rao.
    */
    Dog(const Dog& src); 
    ~Dog();
};

#endif
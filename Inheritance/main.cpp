#include "player.h"

class Parent
{
public:
    void PrintInfo()
    {
        std::cout << "Parent info" << std::endl;
    }

    int member{0};
};

class Child : public Parent
{
public:
    void PrintInfo()
    {
        std::cout << "Child info" << std::endl;
    }

    int member{1};
};

int main()
{
    /*
    Next printed line demonstrates empty Person constructor called automatically in
    empty Player constructor even though we didn't write it explicitly.
    */
    Player pl1;
    std::cout << pl1 << std::endl;

    /*
    Next printed line demonstrates overloaded Player constructor where Player
    constructor called explicitly
    */
    Player pl2("john", "smith", "baseball");
    std::cout << pl2 << std::endl;

    /*
    Next printed line demonstrates how with the initialization list syntax in
    the Player copy constructor calls the Person copy constructor on a
    Player and extracts a copy of the Person within that Player
    */
    Player pl3(pl2);
    std::cout << pl3 << std::endl;

    /*
    This demo shows method overriding in C++ in that when you call PrintInfo on a Child
    directly, it will use the Child implementation. You have to explicitly called the
    Parent one with using .Parent::. A similar thing occurs for members, i.e. that you
    can redefine a member with the same name in the Child as in the Parent. You can
    access the Parent one in the same manner. This is more for demonstration, as you
    shouldn't be accessing fields like this anyway.

    Note, within Child you can access Parent members with syntax like Parent::PrintInfo()
    */
    Child c;
    c.PrintInfo();
    std::cout << c.member << std::endl;
    c.Parent::PrintInfo();
    std::cout << c.Parent::member << std::endl;

    /*
    Observe that after main when these Players go out of scope, that the
    destructors are called in this order: Player destructor for pl3, Person
    destructor for pl3, Player destructor for pl2, Person destructor for pl2,
    Player destructor for pl1, Person destructor for pl1. Or in summary, for a
    given object, the destructors are called going from the most derived class
    to the base class of the inheritance hierarchy.
    */
    return 0;
}
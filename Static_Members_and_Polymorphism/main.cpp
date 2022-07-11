#include <iostream>

class Parent
{
public:
    static int parent_count;
    Parent()
    {
        parent_count++;
    }
};

/*
Static member initialization:
https://stackoverflow.com/questions/185844/how-to-initialize-private-static-members-in-c
*/
int Parent::parent_count = 0;

class Child : public Parent
{
public:
    static int child_count;
    Child()
    {
        child_count++;
    }
};

int Child::child_count = 0;

int main()
{
    Parent p;
    Child c;

    /*
    Note that Child inherits the static field parent_count from Parent
    and thus can be accessed via Parent:: or Child::.
    */
    std::cout << Parent::parent_count << std::endl;
    std::cout << Child::parent_count << std::endl;
    std::cout << Child::child_count << std::endl;
    return 0;
}
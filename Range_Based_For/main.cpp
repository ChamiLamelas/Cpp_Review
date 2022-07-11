#include <iostream>

class Class
{
public:
    Class()
    {
        std::cout << "Class constructor called" << std::endl;
    }
    Class(const Class &source)
    {
        std::cout << "Class copy constructor called" << std::endl;
    }
};

int main()
{
    Class objs[]{Class(), Class(), Class()};

    /*
    Range based for loop by default will not copy the collection (objs) but
    it will copy the elements of objs. Therefore, if performing read-only
    operations on the elements with big elements, use a const reference which
    can be done with auto. Observe below, copy constructor is called 3x only
    with the for loop.
    
    https://docs.microsoft.com/en-us/cpp/cpp/range-based-for-statement-cpp?view=msvc-170
    https://stackoverflow.com/questions/51387535/c-range-based-for-loop-is-the-container-copied
    */
    for (auto e : objs)
    {
    }


    for (const auto &e : objs)
    {
    }

    return 0;
}
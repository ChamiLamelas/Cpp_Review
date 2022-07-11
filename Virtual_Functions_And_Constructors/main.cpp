#include <iostream>

class Parent
{
public:
    Parent()
    {
        SetUp();
    }

    virtual void SetUp()
    {
        std::cout << "Parent SetUp called" << std::endl;
    }
};

class Child : public Parent
{
public:
    Child() 
    {
    }
    virtual void SetUp() override
    {
        std::cout << "Child SetUp called" << std::endl;
    }
};

int main()
{
    /*
    In C++, an overriden virtual method in a child class will not
    be the one that runs if it's called in the parent class constructor
    as shown below. It's because the parent class is entirely set up
    first before the child, see the article here: 
    https://stackoverflow.com/questions/962132/calling-virtual-functions-inside-constructors

    In Java, this is allowed but discouraged because it can lead to bugs,
    see this article:
    https://stackoverflow.com/questions/3404301/whats-wrong-with-overridable-method-calls-in-constructors

    Example, this Java code displays "Child setup called"

    public class Parent {
        public Parent() { setup(); }
        public void setup() { System.out.println("Parent setup called"); }
    }
    public class Child extends Parent {   
        public void setup() { System.out.println("Child setup called"); }
    }

    Main: Child c = new Child();
    */
    Child c;
    return 0;
}
#include <iostream>

// Rao section 9 and 12 mention the importance of a move
// constructor to avoid multiple copies when involving
// temporary objects
class MyClass {
   private:
    int i;

   public:
    MyClass(int j) : i(j) {
        std::cout << "constructor called" << std::endl;
    }
    MyClass(const MyClass &src) {
        std::cout << "copy constructor called" << std::endl;
        this->i = src.i;
    }

    // Without this, main() should print copy constructor
    // called twice - when move is provided, it should print
    // copy constructor called and move constructor called
    // however, this doesn't show up on my computer due to
    // https://en.wikipedia.org/wiki/Copy_elision
    // which is a built in C++ optimization to use copy
    // constructor to create a temporary object that will be
    // copied from immediately and destroyed.
    MyClass(const MyClass &&src) {
        std::cout << "move constructor called" << std::endl;
        this->i = src.i;
    }
    int GetI() const { return i; };
};

MyClass Copy(const MyClass &src) {
    MyClass c{src.GetI()};
    return c;
}

int main() {
    MyClass c{1};
    // Copy constructor of MyClass is called once with the
    // creation of c2 from the returned MyClass from Copy(c)
    // Copy constructor is also called in creating the
    // temporary object returned by Copy(c) that is a copy
    // of c constructed inside Copy
    MyClass c2{Copy(c)};
}
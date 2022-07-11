#include <iostream>

class Parent
{
public:
    virtual ~Parent(){};
};
class Child : public Parent
{
public:
    void Func()
    {
        std::cout << "Child member function" << std::endl;
    }
};

int main()
{
    Child c;
    Parent *parent_ptr{&c};
    Parent &parent_ref{c};

    // Fail to compile Func() is in Child not in Parent
    // parent_ptr->Func();
    // parent_ref.Func();

    /*
    Need Child pointer or reference. We can get one from a Parent pointer
    using dynamic_cast. Note in order to use a dynamic_cast, the Parent
    class must be "polymorphic" which means it must have one virtual
    function (see: https://stackoverflow.com/a/15114118). For good
    practice, let's make a virtual default destructor.

    If this fails (e.g. the cast can't be done, say if Child was not
    a derived class of Parent), child_ptr is set to nullptr.

    Note dynamic casting a lot is considered bad practice and shouldn't
    be used too much.
    */
    Child *child_ptr{dynamic_cast<Child *>(parent_ptr)};

    /*
    Can also do with references, but there isn't a clear failure signifier
    like nullptr with pointers, so do this with caution.
    */
    Child &child_ref{dynamic_cast<Child &>(parent_ref)};

    child_ptr->Func();
    child_ref.Func();

    return 0;
}
#include <iostream>
#include <memory>

/*
Looking at Rao Lesson 26

Deep Copy pointers - everytime there is a smart pointer copy is done,
a deep copy is made. Thus, I assume that each smart pointer knows
to delete because a heap allocation is made.

=> Don't understand how this is good, seems to defeat the purpose
of being a pointer to ensure safe deletion. Just like copying objects
by value.

Copy on Write pointers - creates a copy of data only when a non-const
function is called.

=> Again, this doesn't seem like it is good for pointers because a
copy is being made of the data. So, other pointers will now
be pointing to different data.

Reference-Counted Smart Pointers - keeps track of number of pointers
to some object and deletion of heap resource is done after no
more pointers refer to some object (this seems like what Java does).
Reference-Linked pointers seem to be some adaptation of this.

Destructive Copy Smart pointers - destroys an object after a pointer
copy and ensures only 1 pointer refers to some heap allocated object.

=> Even book discourages use of these.

In general: A lot of things aren't explained. Can we use raw pointers
with smart pointers? Like can we make raw pointer references to
smart pointers. This seems necessary, but it is never discussed.
*/

class Class
{
public:
    ~Class() { std::cout << "Class destructor" << std::endl; }
};

int main()
{
    // Observe by print that destructor is called as unique_ptr auto calls delete given a
    // pointer from heap allocation
    std::unique_ptr<Class> obj(new Class);
    return 0;
}
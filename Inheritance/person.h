#ifndef PERSON_H
#define PERSON_H

#include <string_view>
#include <string>
#include <iostream>

class Person
{
    /*
    Allows for Person objects to be printed to an output stream provided
    a Person and an output stream (e.g. cout). Not described in detail
    in video, seems to follow this guide:
    https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

    Can declare a function (such as operator<<) as a friend as follows.
    Can also declare a class as a friend with friend class <ClassName>;

    Note also it doesn't matter if the friend is put in a private section
    (as it is done here b/c members are default private in classes) or in
    a public section (see article: https://stackoverflow.com/a/6407710)
    */
    friend std::ostream &operator<<(std::ostream &out, const Person &person);

public:
    Person();
    Person(std::string_view fn, std::string_view ln);

    /*
    We define a copy constructor for this demo, but note that a default
    one will be provided by the compiler that will work just fine
    for Person as it does not need any special accomodations to ensure
    a deep copy (i.e. it's not working with pointers/dynamically
    allocated memory).
    */
    Person(const Person& source);
    ~Person();

    /*
    We have to mark these two functions as const so they can be called on
    const objects (as they do not modify member variables). To see how
    this works under the hood, see here: https://stackoverflow.com/a/3141107.
    Note defining a function as const restricts you from modifying any
    member variables (error is expression must be modifiable lvalue). By
    marking a function const, C++ seems to mark all member variables as 
    no longer modifiable lvalues.

    We have to specifically do this for this demo because operator<< for
    Player objects takes a const Player and since Player can only access
    first_name, last_name via these member functions, they are called
    there (and to compile, must be marked const).

    This is more powerful than the capabilities of final in Java. Consider
    this Java code:
    
    public class Child {
        private int x;
        public Child() { x = 0; }
        public void change() { x++; }
    }

    Main: 

    final Child c = new Child();
    c.change();

    This is perfectly fine. final stops Java references from pointing to something
    else (like c = null). Thinking of Java references like C++ pointers (discussed
    previously in Statements and Functions), this would be more like adding a const
    after * for a C++ pointer (recall: https://stackoverflow.com/a/1143272). A
    C++ const at the beginning restricts modification to member variables.
    */
    const std::string &GetFirstName() const;
    const std::string &GetLastName() const;

private: 
    /*
    If we make member variables protected in a base class, they will be
    accessible in derived classes that do public inheritance but not in 
    outside files.
    */
    std::string first_name;
    std::string last_name;

};

#endif
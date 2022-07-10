#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"

/*
In the line class Derived : x base, x denotes the base access specifier. x can
be public, protected, or private. This affects use of base members in both
the implementation of the derived class and in main code. These also severely
restrict future inheritance of Derived.

With public inheritance, everything in the base class maintains access specifier,
this mimics Java inheritance.

public member in base is public in derived
protected member in base is protected in derived
private members of base remain unaccessible to derived

With protected inheritance, public base class members are secured to protected:

public member in base is protected in derived
protected member in base is protected in derived
private members of base remain unaccessible to derived

With private inheritance public and protected base class members are secured to
private:

public member in base is private in derived
protected member in base is private in derived
private members of base remain unaccessible to derived

See also Rao Lesson 10.

There is a way to reverse private inheritance to some extent in the Derived class
with the using keyword under the desired access specifier (but this seems pointless
because if we don't want to reduce access, why use private inheritance to start with?).
Note this can't be used in the Derived class to reverse something being private in the
Base class. Only to reverse things that become private in Derived that were protected
or public in Base.

See ~1:00:35:00 in the video
*/
class Player : public Person
{
    friend std::ostream &operator<<(std::ostream &out, const Player &player);

public:
    /*
    Can also inherit the base constructor with the syntax: using Person::Person
    which means that if we were to omit a constructors for Player, the
    compiler will automatically make a default constructor for Player that
    will only initialize Person's member variables in the Player. He says (and I
    agree) that this is bad practice as it can lead to confusion.
    */
    Player();
    Player(std::string_view first_name, std::string_view last_name, std::string_view g);

    // Copy constructor defined here because how do we copy the Person inside a Player?
    Player(const Player &source);
    ~Player();

private:
    std::string game;
};

#endif
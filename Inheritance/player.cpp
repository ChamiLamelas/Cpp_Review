#include "player.h"

Player::Player()
{
    std::cout << "Empty Player constructor called" << std::endl;
}

/*
To call an overloaded base constructor from a derived class, use
initialization lists as follows (Rao Lesson 10).

In the video, he recommends doing this with protected members in
the base class initially, later talks about these lists.

Important to note that initializer lists cannot be used to
initialize member variables that are private in base classes.
*/
Player::Player(std::string_view first_name, std::string_view last_name, std::string_view g) : Person(first_name, last_name), game(g)
{
    std::cout << "Overloaded Player constructor called" << std::endl;
}

Player::Player(const Player &source) : Person(source), game(source.game)
{
    std::cout << "Player copy constructor called" << std::endl;
}

Player::~Player()
{
    std::cout << "Player destructor called for " << *this << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << player.GetFirstName() << " " << player.GetLastName() << " " << player.game;
    return out;
}

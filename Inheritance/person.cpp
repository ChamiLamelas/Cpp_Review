#include "person.h"

Person::Person()
{
    std::cout << "Empty Person constructor called" << std::endl;
}

Person::Person(std::string_view fn, std::string_view ln) : first_name(fn), last_name(ln)
{
    std::cout << "Overloaded Person constructor called" << std::endl;
}

Person::Person(const Person &source) : first_name(source.first_name), last_name(source.last_name)
{
    std::cout << "Person copy constructor called" << std::endl;
}

Person::~Person()
{
    std::cout << "Person destructor called for " << *this << std::endl;
}

const std::string &Person::GetFirstName() const
{
    return first_name;
}

const std::string &Person::GetLastName() const
{
    return last_name;
}

// Note this is a non-member function, put we put it here b/c its implementation is related
std::ostream &operator<<(std::ostream &out, const Person &person)
{
    out << person.first_name << " " << person.last_name;
    return out;
}

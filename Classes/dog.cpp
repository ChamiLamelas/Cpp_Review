#include "dog.h"
#include <iostream>

Dog::Dog(std::string_view breed, std::string_view name, int age)
{
    this->breed = breed;
    this->name = name;
    this->age = new int(age);
}

Dog::Dog(const Dog &src)
{
    this->breed = src.breed;
    this->name = src.name;
    this->age = new int(*(src.age));
}

Dog::~Dog()
{
    std::cout << age << std::endl;
    delete age;
    std::cout << "Dog destructor successful for Dog with name: " << name << " breed: " << breed << std::endl;
}

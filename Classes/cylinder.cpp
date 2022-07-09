#include <numbers>
#include <cmath>

/*
Note for splitting up class definition, must include header unlike with
splitting up functions! Without this, won't see ThirdCylinder to implement
here.
*/
#include "cylinder.h"

ThirdCylinder::ThirdCylinder()
{
    this->base_radius = 1.0;
    this->height = 1.0;
}

/*
Alternative form of initializing member variables is using what's called an
initialization list. Note, for this to be possible, the parameter names must
be different than the member variable names (as this-> cannot be used in
the list). See Rao Lesson 9.
*/
ThirdCylinder::ThirdCylinder(double b_r, double h) : base_radius(b_r), height(h) {}

double ThirdCylinder::GetBaseRadius()
{
    return base_radius;
}

double ThirdCylinder::GetHeight()
{
    return height;
}

void ThirdCylinder::SetBaseRadius(double base_radius)
{
    this->base_radius = base_radius;
}

void ThirdCylinder::SetHeight(double height)
{
    this->height = height;
}

double ThirdCylinder::Volume()
{
    return std::numbers::pi * std::pow(base_radius, 2) * height;
}

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

ThirdCylinder::ThirdCylinder(double base_radius, double height)
{
    this->base_radius = base_radius;
    this->height = height;
}

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

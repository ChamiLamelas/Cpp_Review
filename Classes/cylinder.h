#ifndef CYLINDER_H
#define CYLINDER_H

class ThirdCylinder
{
private:
    double base_radius;
    double height;

public:
    /*
    Don't need to leave implementations empty, can implement some stuff here.
    But make sure you don't define something here if you will also define it
    in cpp! Linker will fail (build).
    */
    ThirdCylinder();
    ThirdCylinder(double base_radius, double height);
    double GetBaseRadius();
    double GetHeight();
    void SetBaseRadius(double base_radius);
    void SetHeight(double height);
    double Volume();
};

#endif
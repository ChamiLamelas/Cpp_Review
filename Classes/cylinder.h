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
    ThirdCylinder(double b_r, double h);

    /*
    Here, the member variables that are retrieved with these getters are
    (small size) primitives so it is okay to return by value. However,
    one could ask the question, if returning (say a big) type T should
    getters return T or const T&? There doesn't seem to be a full
    consensus on this, see here: 
    https://stackoverflow.com/a/2182451
    https://stackoverflow.com/a/134777
    https://stackoverflow.com/a/136053

    A similar argument most likely could be applied for string getters
    to return string v. string_view (in place of const string&).
    */
    double GetBaseRadius();
    double GetHeight();
    void SetBaseRadius(double base_radius);
    void SetHeight(double height);
    double Volume();
};

#endif
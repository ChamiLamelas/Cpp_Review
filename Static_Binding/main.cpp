#include <iostream>

// Class hierarchy: Base Shape, Derived Oval, Circle
class Shape
{
public:
    void draw()
    {
        std::cout << "shape drawn" << std::endl;
    }
};

class Oval : public Shape
{
public:
    Oval() : x_radius(1.0), y_radius(1.0) {}
    Oval(double x_rad, double y_rad) : x_radius(x_rad), y_radius(y_rad) {}

    void draw()
    {
        std::cout << "oval drawn, x radius = " << x_radius << " y radius = " << y_radius << std::endl;
    }

private:
    double x_radius;
    double y_radius;
};

class Circle : public Shape
{
public:
    Circle() : radius(1.0) {}
    Circle(double rad) : radius(rad) {}
    void draw()
    {
        std::cout << "circle drawn, radius = " << radius << std::endl;
    }

private:
    double radius;
};

// See discussion in main for why we pass by reference, pointer here
void UseShape(Shape &shape)
{
    shape.draw();
}
void UseShape(Shape *shape)
{
    shape->draw();
}

int main()
{
    Shape shape;
    Oval oval;
    Circle circle;

    /*
    Why is it that we store derived classes (Oval, Circle) in pointers (and
    later references) of the base (Shape)? If we were to write instead
    Shape oval_shape(oval), this would only copy the Shape part of the Oval
    oval into oval_shape. This was seen before when we were implementing
    the copy constructor of Player in Inheritance. When it is done accidentally
    here this is known as Slicing (see Rao Lesson 10). This can also occur
    if we have a pass by value function like void UseShape(Shape input) and
    then we call UseShape(oval) because again the Shape copy constructor is
    used. Instead of passing by value or storing derived classes in a base,
    use pointers or (optionally const) references to avoid slicing. That is,
    change to void UseShape(Shape& input) or void UseShape(Shape* input) or
    do Shape *oval_shape{&oval} or Shape &oval_shape{oval}.
    */
    Shape *shape_ptr1{&shape};
    Shape *shape_ptr2{&oval};
    Shape *shape_ptr3{&circle};

    Shape &shape_ref1{shape};
    Shape &shape_ref2{oval};
    Shape &shape_ref3{circle};

    /*
    Here is a related thing, if we want to store a collection of derived
    objects, we need to have the collection be of a base pointer type since
    arrays of references are disallowed, see: https://stackoverflow.com/a/1164306
     */
    Shape *shape_ptrs[]{&shape, &oval, &circle};

    /*
    Static binding with pointers is what occurs when the compiler just sees the
    type of the pointer and uses the member function based on that versus on
    the derived object that may be referenced. In this case, since all these
    pointers are Shape *, regardless of the object pointed to, the draw() method
    of Shape is called.
    */
    std::cout << "Static binding: pointers" << std::endl;
    shape_ptr1->draw();
    shape_ptr2->draw();
    shape_ptr3->draw();

    /*
    Static binding with references is what occurs when the compiler just sees the
    type of the reference and uses the member function based on that versus on
    the derived object that may be referenced. In this case, since all these
    references are Shape &, regardless of the object pointed to, the draw() method
    of Shape is called.
    */
    std::cout << "Static binding: references" << std::endl;
    shape_ref1.draw();
    shape_ref2.draw();
    shape_ref3.draw();

    /*
    More instances of static binding with pointers and references, this time
    when we have functions.
    */
    std::cout << "Static binding: function taking base pointer" << std::endl;
    UseShape(shape_ptr1);
    UseShape(shape_ptr2);
    UseShape(shape_ptr3);

    std::cout << "Static binding: function taking base reference" << std::endl;
    UseShape(shape_ref1);
    UseShape(shape_ref2);
    UseShape(shape_ref3);

    /*
    Another instance of static binding with pointers, this is repetitive but it
    illustrates a similar thing where we want polymorphism (a collection of base
    type pointers).
    */
    std::cout << "Static binding: collection of base pointers" << std::endl;
    for (auto e : shape_ptrs)
    {
        e->draw();
    }

    return 0;
}
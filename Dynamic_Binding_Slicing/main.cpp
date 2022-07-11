#include <iostream>
#include <numbers>
#include <cmath>

// Class hierarchy: taken from Static_Binding and modified
class Shape
{
public:
    // You should not use default arguments with virtual functions as it can lead to strange results
    virtual void draw()
    {
        std::cout << "shape drawn" << std::endl;
    }
};

class Oval : public Shape
{
public:
    Oval() : x_radius(1.0), y_radius(1.0) {}
    Oval(double x_rad, double y_rad) : x_radius(x_rad), y_radius(y_rad) {}

    /*
    It is good to mark overriden methods with override in inheritance
    hierarchies with virtual functions. The compiler will make sure that
    draw() actually exists in Shape. If we say wrote this draW then made
    Shape *s{&oval} and did s->draw() it would still call Shape draw
    because it couldn't find a draw in Oval (so compilation and runtime
    pass, but we get a weird result).

    Also, it is not required that overriden virtual methods in the
    derived class are also marked virtual, in fact the virtual is
    carried down the inheritance hierarchy. However, it is considered
    good practice to include the virtual to indicate that it is
    a function being passed down the inheritance hierachy and will
    be executed following polymorphism rules at runtime.
    */
    virtual void draw() override
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
    virtual void draw() override
    {
        std::cout << "circle drawn, radius = " << radius << std::endl;
    }

    /*
    If we have a method only available in a derived class, marking it
    virtual does not mean it can be called on a base pointer as the
    member function does not exist in the base class.
    */
    virtual double area()
    {
        return std::numbers::pi * std::pow(radius, 2);
    }

private:
    double radius;
};

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

    Shape *shape_ptr1{&shape};
    Shape *shape_ptr2{&oval};
    Shape *shape_ptr3{&circle};

    Shape &shape_ref1{shape};
    Shape &shape_ref2{oval};
    Shape &shape_ref3{circle};

    Shape *shape_ptrs[]{&shape, &oval, &circle};

    /*
    With dynamic/late binding (enabled using virtual), C++ will look at the object
    that is actually being managed by a Shape * pointer or referenced by a Shape&
    and use that object's draw method. The following examples all show this.
    */

    std::cout << "Dynamic binding: pointers" << std::endl;
    shape_ptr1->draw();
    shape_ptr2->draw();
    shape_ptr3->draw();

    std::cout << "Dynamic binding: references" << std::endl;
    shape_ref1.draw();
    shape_ref2.draw();
    shape_ref3.draw();

    std::cout << "Dynamic binding: function taking base pointer" << std::endl;
    UseShape(shape_ptr1);
    UseShape(shape_ptr2);
    UseShape(shape_ptr3);

    std::cout << "Dynamic binding: function taking base reference" << std::endl;
    UseShape(shape_ref1);
    UseShape(shape_ref2);
    UseShape(shape_ref3);

    std::cout << "Dynamic binding: collection of base pointers" << std::endl;
    for (auto e : shape_ptrs)
    {
        e->draw();
    }

    // Trying to call (virtual) derived member function on base pointer causes compilation failure
    // std::cout << shape_ptr3->area() << std::endl;
    // std::cout << shape_ref3.area() << std::endl;

    /*
    Note that the sizes are larger than the versions in Static_Binding
    This is because virtual functions greatly increase object size
    in order to support dynamic binding
    */
    std::cout << sizeof(Shape) << " " << sizeof(Oval) << " " << sizeof(Circle) << std::endl;

    /*
    Here is an example of slicing. Despite marking Circle::draw as virtual, we
    still see Shape::draw output below. This is because of slicing happening
    as only the Shape members of Circle are copied into sliced_shape from circle.

    We can see with the printed sizes that the size of the sliced shape matches
    that of a Shape not a Circle.
    */
    Shape sliced_shape{circle};
    sliced_shape.draw();
    std::cout << sizeof(sliced_shape) << " " << sizeof(circle) << std::endl;

    // This also applies if we store the objects in a Shape collection
    Shape sliced_shapes[]{oval, circle};
    sliced_shapes[0].draw();
    std::cout << sizeof(sliced_shapes[0]) << " " << sizeof(oval) << std::endl;
    sliced_shapes[1].draw();
    std::cout << sizeof(sliced_shapes[1]) << " " << sizeof(circle) << std::endl;

    return 0;
}
#include <iostream>
#include <numbers>
#include <cmath>
#include <string_view>

// Class hierarchy: taken from Dynamic_Binding_and_Slicing and modified
class Shape
{
public:
    virtual void draw()
    {
        std::cout << "shape drawn" << std::endl;
    }

    virtual void draw(std::string_view message)
    {
        std::cout << "shape drawn " << message << std::endl;
    }
};

class Oval : public Shape
{
public:
    Oval() : x_radius(1.0), y_radius(1.0) {}
    Oval(double x_rad, double y_rad) : x_radius(x_rad), y_radius(y_rad) {}

    /*
    Here the virtual was removed from the declaration as this
    version of draw() should not be overriden (as it is marked
    final now). The purpose of virtual is really to ensure that
    at runtime, the most derived version of this method is
    executed on the runtime instance. If a method is final,
    there will be no such more derived version.
    */
    void draw() override final
    {
        std::cout << "oval drawn, x radius = " << x_radius << " y radius = " << y_radius << std::endl;
    }

    /*
    Non virtual functions are final by default as they cannot
    be overriden. Overriding a method really implies that the
    method being overriden is a virtual method. If there was
    a class that derived from Oval and included a BiggerRadius
    function, it would really be hiding this BiggerRadius, not
    overriding it, which cannot be prevented without making this
    virtual and final (which wouldn't intuitively make sense).

    https://stackoverflow.com/questions/17641736/preventing-overriding-and-or-hiding-base-class-function-c-11
    https://stackoverflow.com/questions/24545729/why-is-it-not-possible-to-define-a-non-virtual-method-as-final-in-c11
    */
    double BiggerRadius() {
        return x_radius >= y_radius ? x_radius : y_radius;
    }

private:
    double x_radius;
    double y_radius;
};

/*
Marking a class as final will mean that this class cannot serve as a
base class for any other class.
*/
class Circle final : public Shape
{
public:
    Circle() : radius(1.0) {}
    Circle(double rad) : radius(rad) {}

    /*
    virtual has been removed as it makes to sense as there will be no
    derived classes of Circle for which you would have something like
    Circle *x{&derived} and when you do x->draw() require dynamic binding
    enabled by virtual.
    */
    void draw() override
    {
        std::cout << "circle drawn, radius = " << radius << std::endl;
    }

private:
    double radius;
};

// Fails to compile (Circle is final)
// class SpecialCircle: public Circle {};

class SpecialOval: public Oval {
    // Fails to compile draw() in Oval is final
    // void draw();

    // Compiles b/c this is hiding (not overriding)
    double BiggerRadius() {

    };
};

int main()
{
    Shape shape;
    Oval oval;
    Circle circle;

    Shape *shape_ptr1{&shape};
    Shape *shape_ptr2{&oval};
    Shape *shape_ptr3{&circle};

    /*
    Using base class (Shape) pointers we can call both overloads
    of the Shape's draw function, using the appropriate version
    of draw() based on the derived class using dynamic binding.
    */
    shape_ptr1->draw();
    shape_ptr2->draw();
    shape_ptr3->draw();

    shape_ptr1->draw("shape");
    shape_ptr2->draw("oval");
    shape_ptr3->draw("circle");

    // We can call draw() on all 3 objects as Circle, Oval override it
    shape.draw();
    oval.draw();
    circle.draw();

    /*
    We can only call draw(s) on Shape because when only 1 of a base's overloaded
    function's versions is overriden in derived classes, the other versions of
    the function are lost. This leads to compilation failure in the derived classes.
    In order to fix this issue, all versions of an overloaded function must be
    overriden. Note, if we did not override draw() in Circle and Oval then
    we would not have this issue.

    Also, the overloaded versions that are not overriden are lost to downstream
    classes in the hierarchy (say if classes existed that were derived from Oval
    or Circle).

    Note, this issue does not exist in Java, suppose we have the Java class
    hierarchy:

    public class Parent {
        public void print() { System.out.println("Parent"); }
        public void print(String s) { System.out.println("Parent " + s); }
    }

    public class Child extends Parent {
        public void print() { System.out.println("Child"); }
    }

    This main code would work just fine:

    Parent p = new Child();
    p.print("hello");
    p.print();

    Child c = new Child();
    c.print("hello");
    c.print();

    It displays:

    Parent hello
    Child
    Parent hello
    Child
    */
    shape.draw("shape");
    // oval.draw("oval");
    // circle.draw("circle");

    return 0;
}
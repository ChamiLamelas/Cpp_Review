#include <iostream>
#include "functions.h"
#include <string>

/*
Variables named as all lowercase with underscores, functions with mixed case (starting with caps) following
Google C++ style guide: https://google.github.io/styleguide/cppguide.html#Function_Names
*/
int AddNumbers(int first_num, int second_num)
{
    return first_num + second_num;
}

int Max(int first_num, int second_num)
{
    return first_num >= second_num ? first_num : second_num;
}

/*
To overload a function, they must have different signatures. A C++ function's signature is its name
and number and types of parameters. In other words, to overload a function it cannot just have a
different return type. The function that is called among overloaded functions is based on the function
that matches the signature.

For instance, suppose we removed the above Max and added:

double Max(double first_num, int second_num) {
    return first_num >= second_num ? first_num : second_num;
}

double Max(int first_num, double second_num) {
    return first_num >= second_num ? first_num : second_num;
}

If we called Max on two integers, this code fails to compile because it's ambiguous which Max
should be called because there is no way to choose between the two above Max for two integers (Do
you pick the first or second integer to be cast to double?)
*/
double Max(double first_num, double second_num)
{
    return first_num >= second_num ? first_num : second_num;
}

int main()
{
    /*
    {...} is known as list initialization (some of its benefits include more tightly controlling the type of the values passed
    into the curly brackets based on the LHS data type v. the assignment with = - see this article:
    https://stackoverflow.com/questions/18222926/what-are-the-advantages-of-list-initialization-using-curly-braces)

    It is not clear if this is always better however as this creates an initializer_list object (see here
    https://stackoverflow.com/questions/13267277/where-can-we-use-list-initialization)
    that many standard types (and collections) use to support initialization storing values specified via {val1, val2, ...}
    versus repeated calls (e.g. push_back for building a std::vector). {} defaults to behaving like () for objects when no
    initializer_list constructor exists (see here: https://stackoverflow.com/questions/15396124/calling-constructor-with-braces)
    */
    int first_number{3};
    int second_number{7};

    std::cout << "First: " << first_number << std::endl;
    std::cout << "Second: " << second_number << std::endl;

    std::cout << "First + Second: " << AddNumbers(first_number, second_number) << std::endl;

    /*
    Expect an AddNumbers function to return 20 for this, but since AddNumbers was defined for ints
    it will implicitly narrow the precision of the doubles 13.3 and 6.7 to 13 and 6 respectively
    because it takes ints, yielding 19.
    */
    std::cout << "AddNumbers(First, Second) (Doubles): " << AddNumbers(13.3, 6.7) << std::endl;

    /*
    Demonstrates by default, arguments are passed by value (i.e. a copy is worked with inside a function).
    Changes to the copy do not affect the argument.

    Also shows how a function can be used with just declaration loaded prior
    */
    int x{1};
    PassByValue(x);
    std::cout << "Inside main: x = " << x << " Address: " << &x << std::endl;

    /*
    When a pointer is passed to a function it is also by default passed by value. This output demonstrates
    two things:

    1. PassByPointer makes a copy of the input pointer. Changes to that copy (e.g. setting it to nullptr) has
    no effect on the value of the pointer in main.
    2. PassByPointer, via the pointer, allows for modification of the data pointed to it.
    */
    int y{1};
    int *y_ptr{&y};
    std::cout << "Inside main before: y = " << y << " y_ptr: " << y_ptr << " Address of y_ptr: " << &y_ptr << std::endl;
    PassByPointer(y_ptr);
    std::cout << "Inside main after: y = " << y << " y_ptr: " << y_ptr << " Address of y_ptr: " << &y_ptr << std::endl;

    /*
    When pass by reference is used in C++, we can actually modify the value of the variable being aliased, not
    just its properties. This is different than Java "pass by reference" which is more akin to C++ pass by
    pointer (see https://stackoverflow.com/a/3869589).

    The implementation of C++ pass by reference is most likely done with pointers (see here
    https://stackoverflow.com/a/2936886). It was introduced so the programmer doesn't have to
    bother with pointers + dereferencing as in pass by pointer.

    Note here that the alias used in the method is acting like a C++ reference described in References (it
    shares the same address as z in main).
    */
    int z{1};
    std::cout << "Inside main before: z = " << z << " Address: " << &z << std::endl;
    PassByReference(z);
    std::cout << "Inside main after: z = " << z << " Address: " << &z << std::endl;

    /*
    ReturnByValue and ReturnByValue2 both return values.

    Demo #1 output shows that a copy is made of the returned data in ReturnByValue to be placed in a in main.
    Demo #2 output shows that a copy is sometimes not made of the returned data in ReturnByValue2, that is
    s in main is allocated somehow to hold. This simulates returning by reference in the sense that an extra
    copy is not made. This is known as Return Value Optimization (RVO), the details of (i) how it is implemented and
    (ii) when it can be done by the compiler is not clear. What I can get from this demo is that since the
    return value is being used to initialize a higher storage object (string v. int) it has chosen to make this
    optimization.
    Demo #3 output shows that RVO is not always done even with higher storage objects. Here, we have the return
    done upon an assignment to s2 (as s2 was initialized to the empty string). I am not sure why RVO is not done
    here, but we can see that an extra copy is made.

    The takeaway is to not use return by value if its possible that an extra copy of a high storage object will
    be made. Instead, one can pass in an output parameter to be filled in someway that is a reference parameter.
    One needs to be careful with returning by reference because local variables cannot be returned by reference,
    only objects that will not be destroyed upon function exit can be returned by reference.

    See discussions here:
    https://stackoverflow.com/questions/7456778/function-in-c-returns-by-value-or-by-reference
    https://stackoverflow.com/questions/19454068/c-return-value-optimization
    https://stackoverflow.com/a/752699
    */
    int a{ReturnByValue()};
    std::cout << "Inside main: &a = " << &a << std::endl;

    std::string s{ReturnByValue2()};
    std::cout << "Inside main: &s = " << &s << std::endl;

    std::string s2{};
    std::cout << "Inside main: &s2 = " << &s2 << std::endl;
    s2 = ReturnByValue2();
    std::cout << "Inside main: &s2 = " << &s2 << std::endl;

    /*
    Lambda function. [] specifies the capture list which can take captures (variables
    from the outer scope that can be used in the lambda function) see here:
    https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture

    ->double specifies the return type as double and is not necessary.

    Use auto to deduce type of lambda function, can also call inline. This doesn't say
    how you would pass a function as a parameter in C++ specifically (maybe use functional
    library?). To do it in C (I assume valid in C++ as well):
    https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c

    Also can look at:
    https://github.com/ChamiLamelas/Learning_C_K_and_R/blob/master/ch6_structures/6.6_table_lookup/chaining_hash_table.c

    This article (requires further reading) discusses it in C++ (note that capture lists cause
    issues):
    https://stackoverflow.com/questions/16111285/how-to-pass-and-execute-anonymous-function-as-parameter-in-c11

    Demo #1 prints demonstrate how capture list is done by copy (addresses are different of c).
    Demo #2 prints demonstrates how capture list is done by reference (addresses are same of d).
    */

    int c{3};
    std::cout << "main &c = " << &c << std::endl;
    auto f = [c](double b) -> double
    {
        std::cout << "lambda &c = " << &c << std::endl;
        // c comes from outer scope via capture list, b is a parameter
        return c + b;
    };
    std::cout << f(2) << std::endl;

    int d{3};
    std::cout << "main &d = " << &d << std::endl;
    auto g = [&d](double b)
    {
        std::cout << "lambda &d = " << &d << std::endl;
        // d comes from outer scope via capture list, b is a parameter
        return d + b;
    };
    std::cout << g(2) << std::endl;

    // Capture all variables in the outer scope by copy
    auto h = [=](double b)
    {
        std::cout << "lambda &d = " << &d << std::endl;
        // d comes from outer scope via capture list, b is a parameter
        return d + b;
    };
    std::cout << h(2) << std::endl;

    // Capture all variables in the outer scope by reference
    auto l = [&](double b)
    {
        std::cout << "lambda &d = " << &d << std::endl;
        // d comes from outer scope via capture list, b is a parameter
        return d + b;
    };
    std::cout << l(2) << std::endl;

    return 0;
}

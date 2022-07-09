#include <iostream>

// strcmp is in std of cstring not string
#include <cstring>

// See below
#include <concepts>
#include <type_traits>
#include <string>

template <typename T>
T Max(T a, T b)
{
    /*
    Assumes T supports >= (if T doesn't compilation fails when it tries to generate the
    appropriate function)
    */
    return (a >= b) ? a : b;
}

/*
This is a better version of Max (note that it cannot be overloaded - see comment in Statements_and_Functions).
This is better because we don't pass by value. a, b can be const references because, to compute max(a,b), we only
need read-only access to them. Furthermore, we can return a reference also because the max(a,b) is either a or b
and thus returning by reference is safe as the returned reference will reference a variable that is guaranteed to
exist upon function exit (warning raised when reference to local variable is returned).
*/
template <typename T>
const T &Max2(const T &a, const T &b)
{
    return (a >= b) ? a : b;
}

/*
This is called template specialization. Without this, if Max is called with const char * it will be comparing
the values of the addresses of const char * a and b. However, suppose we want to compare the contents of
the memory referenced by a and b. Then, we can specify the function below. Now, when Max is called with
const char * arguments, the compiler, instead of generating an appropriate Max, it will use this function
supplied here (which uses strcmp for the desired effect).
*/
template <>
const char *Max<const char *>(const char *a, const char *b)
{
    return std::strcmp(a, b) >= 0 ? a : b;
}

/*
The following 4 functions are 4 equivalent ways of imposting an integral
"concept" on the type of the arguments used with these functions. Concepts
are a C++ 20 feature which allows for constraints on the argument types.
See provided constraints here: https://en.cppreference.com/w/cpp/concepts

add3 uses auto inplace of templating (but still has the same concept). This
is discussed here: https://stackoverflow.com/a/60355539 and
https://en.cppreference.com/w/cpp/language/function_template#Abbreviated_function_template
*/
template <typename T>
requires std::integral<T>
    T add(T a, T b)
{
    return a + b;
}

template <std::integral T>
T add2(T a, T b)
{
    return a + b;
}

auto add3(std::integral auto a, std::integral auto b)
{
    return a + b;
}

template <typename T>
T add4(T a, T b) requires std::integral<T>
{
    return a + b;
}

/*
Concepts can be defined in terms of type traits, i.e. utilities for identifying
the type or traits related to the type of the arguments. See here for the provided
type traits: https://en.cppreference.com/w/cpp/header/type_traits
*/
template <typename T>
concept MyIntegral = std::is_integral_v<T>;

template <typename T>
concept Incrementable = requires(T a)
{
    /*
    Inside requires, put all statements that T should be able to support.
    All should compile.
    */
    a += 1;
    a++;
    ++a;
};

// Function using our concept
template <Incrementable T>
void inc(T a)
{
    a++;
}

template <typename T>
concept TinyType = requires(T t)
{
    // Simple requirement: checks whether this syntax is correct (sizeof operates on T)
    sizeof(T) <= 4;
    // Nested requirement: checks if this condition is actually true (if not, concept will fail)
    requires sizeof(T) <= 4;
};

template <typename T>
concept Addable = requires(T a, T b)
{
    /*
    Compound requirement, this reads: a + b must be valid syntax (T is a type that can be added),
    the addition operation should not yield an exception, and the result of the addition should
    be implicilty convertible to int (https://en.cppreference.com/w/cpp/concepts/convertible_to).
    */
    {
        a + b
    }
    noexcept->std::convertible_to<int>;
};

template <TinyType T>
T TinyAdd(T a, T b)
{
    return a + b;
}

template <Addable T>
T IntConvertibleAdd(T a, T b)
{
    return a + b;
}

// Use || to say type must satisfy at least 1 of 2 requirements
template <typename T>
requires std::integral<T> || std::floating_point<T>
    T IntOrFloatAdd(T a, T b)
{
    return a + b;
}

// Use && to say type must satisfy 2 requirements
template <typename T>
requires TinyType<T> && std::integral<T>
    T TinyIntAdd(T a, T b)
{
    return a + b;
}

int main()
{
    int a{1};
    int b{2};

    double c{1.1};
    double d{2.2};

    /*
    T Max(T, T) serves as a blueprint for the compiler which, based on the arguments
    of a call, will replace T with the data type of the arguments and generates a
    new function that will be run. The compiler generates only one function for a
    particular type T. See this tool: https://cppinsights.io/

    Also, make sure that the arguments are truly of the same type. That is, implicit
    conversion is not done. Say if you did Max(1,2.1), compiler can't create a
    Max(int, double).
    */
    std::cout << Max(a, b) << " " << Max(c, d) << std::endl;

    /*
    To solve the Max(int,double) issue, we can use explicit template arguments. That is,
    we tell the compiler want to replace T with. It will generate the appropriate
    function if one does not already exist.

    The following code works because an implict conversion is made of a from int to double
    to match the explicitly specified double template type.
    */
    std::cout << Max<double>(a, c) << std::endl;

    /*
    The following code demonstrates how the template specialization for const char* is used.
    This can be seen by hovering over Max in the print statement (as VS Code hints at it) and
    by seeing that even if the address f is higher than address e, *e is correctly identified
    as greater than *f. Note here, that to avoid the print statement by default printing
    the contents of const char * variables, we need to perform a special cast, see comments here
    in this answer: https://stackoverflow.com/a/30201642
    */
    const char *e{"b"};
    const char *f{"a"};
    std::cout << "e = " << static_cast<const void *>(e) << " f = " << static_cast<const void *>(f)
              << " max(*e,*f) = " << Max(e, f) << std::endl;

    char c1{1};
    char c2{2};
    char c3{add(c1, c2)}; // OK because char is an integral type (Holds for add2,add3,add4)

    int i1{1};
    int i2{2};
    int i3{add(i1, i2)}; // OK because int is an integral type (Holds for add2,add3,add4)

    double d1{1};
    double d2{2};
    /*
    Compilation fails here as double is not an integral type and doesn't match
    concept integral constraint. Holds for add2,add3,add4
    */
    // double d3{add(d1,d2)};

    std::string s1{"hello"};
    std::string s2{"world"};

    inc(c1);
    inc(i1);
    inc(d1);
    // The following won't compile b/c strings can't be incremented
    // inc(s1);

    int i4{TinyAdd(i1, i2)}; // OK sizeof(int) = 4

    /*
    This fails to compile, sizeof(double) <= 4 syntactically correct but the nested requirement fails
    because sizeof(double) = 8
    */
    // double d4{TinyAdd(d1, d2)};

    int i5{IntConvertibleAdd(i1, i2)};
    double d5{IntConvertibleAdd(d1, d2)};

    // Syntactically + is defined for strings, but it does not satisfy the other aspects of compound requirement
    // std::string s3{IntConvertibleAdd(s1, s2)};

    // Both of these compile because integer is integral and double is floating point
    int i6{IntOrFloatAdd(i1, i2)};
    double d6{IntOrFloatAdd(d1, d2)};

    // Fails to compile because strings are neither integral or floating point
    // std::string s4{IntOrFloatAdd(s1,s2)};

    int i7{TinyIntAdd(i1, i2)};
    float f1{1.1};
    float f2{2.2};

    // Fails to compile because floats are tiny (sizeof(float) = 4) but are not integral
    // float f3{TinyIntAdd(f1, f2)};

    /*
    Can also use concepts to restrict the type of auto, below wouldn't compile b/c int is deduced.
    This use case isn't used much
    */
    // std::floating_point auto x = TinyIntAdd(i1, i2);

    return 0;
}
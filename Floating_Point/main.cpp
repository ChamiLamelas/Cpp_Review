#include <iostream>
#include <iomanip>
#include <limits>

int main()
{

    /*
    Different floating point types. Be careful with suffixes. If we leave f at the end of literal we mean
    to store as double, it will still be first represented as float before being placed into double (see
    number8 example below).
    */
    float number1{1.12345678901234567890f};
    double number2{1.12345678901234567890};
    long double number3{1.12345678901234567890L};

    /*
    iomanip includes setprecision which sets the precision of floating point numbers displayed
    in an output stream like cout: https://en.cppreference.com/w/cpp/io/manip/setprecision

    Float precision: 7, Double precision: 17 (usually around 15, dependent on compiler),
    Long double precision: At least 20 (guaranteed to be at least as good as double)
    */
    std::cout << std::setprecision(20);
    std::cout << "sizeof(number1) = " << sizeof(number1) << "\nnumber1 = " << number1 << std::endl;
    std::cout << "sizeof(number2) = " << sizeof(number2) << "\nnumber2 = " << number2 << std::endl;
    std::cout << "sizeof(number3) = " << sizeof(number3) << "\nnumber3 = " << number3 << std::endl;

    // Scientific Notation
    double number4{1.924e8};
    std::cout << "number4 = " << number4 << std::endl;
    double number5{1.924e-8};
    std::cout << "number5 = " << number5 << std::endl;

    // Edge cases (neither yield errors if stored in floating point types)
    double number6{1};
    double number7{};

    // Infinity (also, adding small numbers to Infinity yields Infinity)
    std::cout << "1/0 = " << number6 / number7 << std::endl;
    std::cout << "-1/0 = " << -number6 / number7 << std::endl; // -Infinity
    std::cout << "0/0 = " << number7 / number7 << std::endl;   // NaN

    // Suffix error (output is the same as that of number1)
    double number8{1.12345678901234567890f};
    std::cout << "number8 = " << number8 << std::endl;

    // Can get limits of floating point types (for more capabilities beyond min, max: https://en.cppreference.com/w/cpp/types/numeric_limits)
    std::cout << "min(float) = " << std::numeric_limits<float>::min() << "\nmax(float) = " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "min(double) = " << std::numeric_limits<double>::min() << "\nmax(double) = " << std::numeric_limits<double>::max() << std::endl;
    std::cout << "min(long double) = " << std::numeric_limits<long double>::min() << "\nmax(long double) = " << std::numeric_limits<long double>::max() << std::endl;

    
}
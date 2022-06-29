#include <iostream>

/*
Some Notes on auto:

- Placeholder for a type to be inferred by the compiler.
  - Hence, it only slows compile time as discussed [here](https://stackoverflow.com/questions/32519082/is-auto-specifier-slower-in-compilation-time).
- Recommended to avoid conversions from happening (good use is with iterator types which tend to be long and unwieldy).
*/

int main() {
    /*
    People seem to indicate using auto liberally. In fact, it can be used to prevent implicit conversions (e.g. with assignment
    initialization below), see here: https://stackoverflow.com/a/6900736

    The type inference is done at compile time, so it would only slow building not execution. However, it is not entirely clear
    when not to use it.
    */

    int bad_int = 2.1f;
    auto actual_float = 2.1f;

    std::cout << "bad_int = " << bad_int << std::endl;
    std::cout << "actual_float = " << actual_float << std::endl;

    unsigned int value {1};
    auto copy_value {value};

    /*
    This demonstrates that auto identified that the type should unsigned in the copy. I did this following this answer: 
    https://stackoverflow.com/a/6435036 (not sure why the author says that using auto here could lead to error because it
    has identified the type properly as an unsigned type).
    */
    copy_value -= 2;
    std::cout << "copy_value = " << copy_value << std::endl;
}
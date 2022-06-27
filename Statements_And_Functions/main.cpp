#include <iostream>

/*
Variables named as all lowercase with underscores, functions with mixed case (starting with caps) following
Google C++ style guide: https://google.github.io/styleguide/cppguide.html#Function_Names
*/
int AddNumbers(int first_num, int second_num) {
    return first_num + second_num;
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

    return 0;
}

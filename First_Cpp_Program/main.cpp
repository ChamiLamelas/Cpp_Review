#include <iostream>

/*
In the past, I thought you should have using namespace std; at the top but people seem inclined to keep
the namespace specfication before members to avoid confusion, see here:
https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice?page=1&tab=scoredesc#tab-top 
*/

int main() {
    std::cout << "Hello World!" << std::endl;
    return 0;
}

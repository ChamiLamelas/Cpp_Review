#include <iostream>

int main()
{
    for (auto i = 1; i <= 100; i++)
    {
        // Print the current player
        std::cout << "Player " << (i % 2 == 0 ? 2 : 1) << ": ";

        // Print what they would say
        if (i % 3 == 0 && i % 5 == 0)
        {
            std::cout << "FizzBuzz\n";
        }
        else if (i % 3 == 0)
        {
            std::cout << "Fizz\n";
        }
        else if (i % 5 == 0)
        {
            std::cout << "Buzz\n";
        }
        else
        {
            std::cout << i << "\n";
        }
    }
    std::cout << std::flush;

    return 0;
}
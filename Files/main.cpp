#include <iostream>
#include <fstream>

int main()
{
    std::fstream file1;

    // Open a file (trunc => create one if one doesn't exist) for reading and writing (specified by in or out)
    // Rao omits trunc here, but it's default true to overwrite files
    file1.open("test.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

    // Always check open was successful
    if (file1.is_open())
    {
        std::cout << "file1 opened successfully!" << std::endl;
        file1.close();
    }

    // Alternate way to open a file in same way
    std::fstream file2("test.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
    if (file2.is_open())
    {
        std::cout << "file2 opened successfully!" << std::endl;
        file2.close();
    }

    // Open a file just for writing (will create a file if test2.txt doesn't exist)
    std::ofstream file3("test2.txt", std::ios_base::out);
    if (file3.is_open())
    {
        std::cout << "file3 opened successfully!" << std::endl;
        file3 << "Writing to text file!" << std::endl;

        // close is necessary to do the save
        file3.close();
    }

    // Open an existing file just for reading (if file doesn't exist, it won't open)
    std::ifstream file4("test3.txt", std::ios_base::in);
    if (file4.is_open())
    {
        std::cout << "file4 opened successfully!" << std::endl;
        std::string current_line;

        // Make sure it is still good to read (no error bit set, EOF bit is included)
        while (file4.good())
        {
            std::getline(file4, current_line);
            std::cout << current_line << std::endl;
        }

        file4.close();
    }

    return 0;
}
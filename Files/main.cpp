#include <iostream>
#include <fstream>
#include <string>

void Filter();
void Demo();

int main()
{
    // Demo();


    Filter();
    return 0;
}

void Filter() {
    // Prepare copy.txt by copy pasting copy-start.txt
    std::string src{"copy.txt"};
    std::string tmp{"copy-tmp.txt"};

    std::ifstream src_r(src, std::ios_base::in);
    if (!src_r.is_open()) {
        std::cout << src + " failed to open (r)" << std::endl;
    }

    std::fstream tmp_rw(tmp, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
    if (!tmp_rw.is_open()) {
        std::cout << tmp + " failed to open (rw)" << std::endl;
    }

    bool first_line{true};
    std::string line;
    while (src_r.good()) {
        std::getline(src_r, line);
        if (line[0] == 'a') {
            continue;
        }

        if (!first_line) {
            tmp_rw << "\n";
        }
        tmp_rw << line;
        if (first_line) {
            first_line = false;
        }
    }
    src_r.close();

    std::ofstream src_w(src, std::ios_base::out | std::ios_base::trunc);
    if (!src_w.is_open()) {
        std::cout << src + " failed to open (w)" << std::endl;
    }

    tmp_rw.clear();
    tmp_rw.seekg(0);
    first_line = true;

    while (tmp_rw.good()) {
        std::getline(tmp_rw, line);
        if (!first_line) {
            src_w << "\n";
        }
        src_w << line;
        if (first_line) {
            first_line = false;
        }
    }

    tmp_rw.close();
    src_w.close();
}

void Demo() {
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
}
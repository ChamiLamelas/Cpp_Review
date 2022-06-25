# C++ Review

June 2022

## Materials

* Beginner to Advanced course on YouTube [here](https://www.youtube.com/watch?v=8jLOx1hD3_o).
  * Associated GitHub repository [here](https://github.com/rutura/The-C-20-Masterclass-Source-Code).
  
## Installation of C++ Compilers (Windows 10)
  
* Go [here](https://en.cppreference.com/w/cpp/compiler_support) to check C++ features supported by various compilers.
* Go [here](https://winlibs.com/) to download MinGW for Windows (includes GCC, Clang C++ compilers for Windows).
  * Extract downloaded Zip, move mingw64 folder to where you wish.
  * Add path to bin/ folder in mingw64 folder to Path environment variable.
  
## Setup of Visual Studio Code

* Install C/C++ extension from Microsoft.
* In Visual Studio Code, make a simple C++ test file. 
* Then, with that file open, go to Terminal > Configure Tasks > C/C++: g++.exe build active file.
* Add "-std=c++23" flag to args in tasks.json to enforce C++ version 23.0 to be used by GCC (use c++20 for clang see [here](https://clang.llvm.org/cxx_status.html)).
  * Can also set a label for the task in tasks.json.
* C/C++ extension provides links on useful information on editing tasks.json.
  * For example, can modify it to build all files in a directory and then write to a specific executable (see [here](https://code.visualstudio.com/docs/cpp/config-mingw#_modifying-tasksjson)).
* To set up intellisense and more go to View > Command Palette > C/C++: Edit Configurations (UI).
  * This adds the c_cpp_properties.json configuration file.

## Building and Running C++ Program

* With a C++ file selected, go to Terminal > Run Task > *Label of task in tasks.json*, this creates an .exe file.
* Can run file.exe with ./file in a terminal window.



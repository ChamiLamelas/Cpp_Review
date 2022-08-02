# C++ Review

*June, 2022*

## Materials

* Beginner to Advanced course on YouTube [here](https://www.youtube.com/watch?v=8jLOx1hD3_o).
  * Associated GitHub repository [here](https://github.com/rutura/The-C-20-Masterclass-Source-Code).
* Sams Teach Yourself C++ in One Hour a Day - [Barnes & Noble](https://www.barnesandnoble.com/w/sams-teach-yourself-c-in-one-hour-a-day-siddhartha-rao/1107087353).
* Other links are in the source files.
  
## Installation of C++ Compilers (Windows 10)
  
* Go [here](https://en.cppreference.com/w/cpp/compiler_support) to check C++ features supported by various compilers.
* Go [here](https://winlibs.com/) to download MinGW for Windows (includes GCC, Clang C++ compilers for Windows).
  * Extract downloaded Zip, move mingw64 folder to where you wish.
  * Add path to bin/ folder in mingw64 folder to Path environment variable.
  
## Setup of Visual Studio Code

* Make sure "Open with Code" option is available in Windows Explorer (can fix with reinstall of VS Code).
* Install C/C++ extension from Microsoft.
* In Visual Studio Code, make a simple C++ test file. 
* Then, with that file open, go to Terminal > Configure Tasks > C/C++: g++.exe build active file.
* Add "-std=c++23" flag to args in tasks.json to enforce C++ version 23.0 to be used by GCC (use c++20 for clang see [here](https://clang.llvm.org/cxx_status.html)).
  * Can also set a label for the task in tasks.json.
* C/C++ extension provides links on useful information on editing tasks.json.
  * For example, can modify it to build all files in a directory and then write to a specific executable (see [here](https://code.visualstudio.com/docs/cpp/config-mingw#_modifying-tasksjson)).
* To set up intellisense and more go to View > Command Palette > C/C++: Edit Configurations (UI).
  * This adds the c_cpp_properties.json configuration file.
* Can also add to args the ability to statically link dependencies when compiling an executable. This is done by adding "-static". This allows for copying over the executable to be run on other Windows machines without having to copy dependencies represented via dynamic link libraries (DLL). 
  * See [this post](https://stackoverflow.com/a/26107550) on the difference in these two types of linking.

## Building and Running C++ Program

* With a C++ file selected, go to Terminal > Run Task > *Label of task in tasks.json*, this creates an .exe file.
  * Faster: after setting a default build task (Terminal > Configure Default Build Task), use Ctrl+Shift+B.
* Can run file.exe with ./file in a terminal window.
* When the task runs it opens a new Visual Studio Code terminal that will cause you to be bumped out of the regular powershell terminal (where you run ./file) even if the build is successful (it will prompt you to press any key to close). Leaving the new terminal open has no effect, you will still get switched to it on subsequent task builds. Can fix this issue following [this StackOverflow article](https://stackoverflow.com/a/67872135). 
 * As mentioned in the article, any issues that do occur with the build are shown (in the nicer) problems tab.

## C++ Terminology

* C++ Core Features: basic rules of C++ (e.g. how {} work)
* Standard Library: provided C++ utilities (e.g. iostream)
  * STL: subset of Standard Library that holds containers.

## One Definition Rule

* One Definition Rule (ODR) on [Wikipedia](https://en.wikipedia.org/wiki/One_Definition_Rule) and [standard](https://en.cppreference.com/w/cpp/language/definition#One_Definition_Rule).
* Cannot declare and define the same variable in the same scope or across multiple files at the global scope. 
  * Defining is assigning a value to a variable.
* Same applies for functions, declaration of a function is the function header, definition is the function body.
* These lead to compilation failure.
* Classes or structs can be defined in multiple files but not in the same [translation unit](https://en.wikipedia.org/wiki/Translation_unit_(programming)) which can be thought of as a single file. 
  * I assume this is allow for multiple class implementations, but why is this not allowed with functions? 
* ODR is enforced by the linker. The linker checks all translation units (source files with included files copied in by the compiler) for definitions (to make sure a function is defined) and that there are not two definitions for the same function.
  * It is just custom (for clarity) to name the implementation of `x.h` as `x.cpp` but the functions could be placed in `y.cpp` because the linker checks all files that are built.

## Miscellaneous Links

* Documentation on C++ precedence [here](https://en.cppreference.com/w/cpp/language/operator_precedence).
* Documentation on basic C++ math functions [here](https://en.cppreference.com/w/cpp/header/cmath).
* Initialization types in C++ [here](https://subscription.packtpub.com/book/programming/9781786465184/1/ch01lvl1sec7/understanding-uniform-initialization) and Initialization of Variables [here](https://cplusplus.com/doc/tutorial/variables/).
* Initializer lists [here](https://cplusplus.com/reference/initializer_list/initializer_list/).





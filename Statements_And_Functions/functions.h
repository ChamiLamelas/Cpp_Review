// Video doesn't include header guards: https://en.wikipedia.org/wiki/Include_guard

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include <string>

/*
Function definition (or prototype): function return type, name, parameters.
Function definitions do not need to include parameter names (just types). Keep
names for documentation purposes.

Use PassByValue with primitive types, marking const doesn't really affect this
because changes made inside the function are not visible outside it anyway.
*/
void PassByValue(int a);

/*
Add const before int so that data pointed to by a_ptr can't be modified while
still using a pointer for more efficient data transfer.

In general, if parameter is read only make pointer const, if parameter will store
some sort of output, make pointer non-const
*/
void PassByPointer(int *a_ptr);

/*
Add const before int so that data stored via reference can't be modified while
still using a reference for more efficient data transfer.

In general, if parameter is read only make reference const, if parameter will store
some sort of output, make reference non-const
*/
void PassByReference(int &a);

int ReturnByValue();

std::string ReturnByValue2();

#endif
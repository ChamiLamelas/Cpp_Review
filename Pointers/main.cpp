#include <iostream>

int main()
{
    /*
    Default constructor initializes it to nullptr (https://stackoverflow.com/questions/1282295/what-exactly-is-nullptr)
    but can also be done explicitly
    */
    int *int_ptr{};
    int *int_ptr_null{nullptr};

    std::cout << int_ptr << " " << int_ptr_null << std::endl;

    // All pointers are of the same size
    double *double_ptr{};
    std::cout << sizeof(int_ptr) << " " << sizeof(double_ptr) << std::endl;

    // Can get address of an existing variable to initialize a pointer
    int int_val{1};
    int *int_ptr_addr{&int_val};

    // Fails to compile can't assign double pointer to address of int
    // double *bad_double_ptr{&int_val};

    // Dereferencing a pointer (reading and writing)
    std::cout << int_val << " " << *int_ptr_addr << std::endl;
    *int_ptr_addr = 2;
    std::cout << int_val << " " << *int_ptr_addr << std::endl;

    // Cannot do this for reason described in Arrays/main.cpp (string literal is const char)
    // char *bad_p_str{"Hello World"};
    const char *p_str{"Hello World"};

    // Dynamic Memory Allocation (allocating space for an integer on the heap - value is garbage)
    int *dma_ptr{new int};
    std::cout << *dma_ptr << std::endl;

    // Can reduce scope of variables using {}
    {
        int small_scope_var{1};
        int *small_scope_ptr{new int};
    }
    /*
    Compilation fails if you try to access either of these here. small_scope_var automatically freed from the
    stack at end of block so that's OK. But, can no longer access pointer to free heap space (resource leak).
    */

    /*
    Mark freed ptrs as null (deleting a null pointer has no effect, deleting a non-null already deleted
    pointer will trigger a crash)
    */
    delete dma_ptr;
    dma_ptr = nullptr;

    // Can allocate on heap with a different initial value
    int *dma_ptr2{new int(1)};
    std::cout << *dma_ptr2 << std::endl;
    delete dma_ptr2;
    dma_ptr2 = nullptr;

    // Multiple pointers to same heap memory
    int *dma_ptr3{new int(2)};
    int *dma_ptr4{dma_ptr3};
    std::cout << dma_ptr3 << " " << dma_ptr4 << "\n"
              << *dma_ptr3 << " " << *dma_ptr4 << std::endl;
    delete dma_ptr3;

    // This will trigger undefined behavior because the memory referenced by this pointer has been freed
    // std::cout << *dma_ptr4 << std::endl;

    dma_ptr3 = nullptr;

    // Careful not to delete freed memory again here! (triggers a crash) Just set to null
    // delete dma_ptr4;

    dma_ptr4 = nullptr;

    /*
    Possible for new to fail to give you heap memory (e.g. you have exhausted it). By default
    if new fails, it throws an exception which can be caught and reported as follows:
    */

    try
    {
        int *dma_ptr5{new int};
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    // Another option is to tell new if it fails to not throw an exception but to return nullptr instead
    int *dma_ptr5{new (std::nothrow) int};

    // Compact check if a pointer is not nullptr (automatically evaluated as a boolean expression)
    if (dma_ptr5)
    {
        std::cout << "dma_ptr5 is not nullptr" << std::endl;
    }

    // Using pointer to demonstrate how stack variable is associated with the same memory location post modification
    int x{1};
    int *y{&x};
    std::cout << y << std::endl;
    x = 2;
    std::cout << y << std::endl;

    // Just to detect when crashes occur
    std::cout << "Program done" << std::endl;

    return 0;
}
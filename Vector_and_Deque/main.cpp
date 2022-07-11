#include <iostream>
#include <vector>
#include <deque>

template <typename T>
void DisplayVector(const std::vector<T> &vector)
{
    std::cout << "[ ";
    for (auto itr = vector.cbegin(); itr != vector.cend(); itr++)
    {
        std::cout << *itr << " ";
    }
    std::cout << "] size = " << vector.size() << " capacity = " << vector.capacity() << std::endl;
}

template <typename T>
void DisplayDeque(const std::deque<T> &deque)
{
    std::cout << "[ ";
    for (auto itr = deque.cbegin(); itr != deque.cend(); itr++)
    {
        std::cout << *itr << " ";
    }
    std::cout << "] size = " << deque.size() << std::endl;
}

int main()
{

    // Creating vectors

    // Empty vector
    std::vector<int> vector1;
    // Won't compile b/c vector doesn't support printing
    // std::cout << vector1 << std::endl;
    DisplayVector(vector1);

    // Vector with specific elements
    std::vector<int> vector2{1, 2, 3, 4, 5};
    DisplayVector(vector2);

    // Vector with 10 zeros
    std::vector<int> vector3(10);
    DisplayVector(vector3);

    // Vector with 10 90s
    std::vector<int> vector4(10, 90);
    DisplayVector(vector4);

    // Vector from another vector
    std::vector<int> vector5(vector4);
    DisplayVector(vector5);

    // Vector from subset of another vector
    std::vector<int> vector6(vector2.cbegin() + 1, vector2.cbegin() + 4);
    DisplayVector(vector6);

    // Warning with initializer list, this creates a vector with 10, not a vector of 10 0s
    std::vector<int> vector7{10};
    DisplayVector(vector7);

    // Can pre-reserve space (capacity) to avoid allocations
    std::vector<int> vector8;
    vector8.reserve(10);
    DisplayVector(vector8);

    // Add to end with push_back (constant time except for resizes)
    std::vector<int> vector9;
    vector9.push_back(1);
    DisplayVector(vector9);

    // Use insert for middle additions (depend on number of elements that are shifted)

    // Insert 1 element at start
    std::vector<int> vector10{1, 2, 3, 4, 5};
    vector10.insert(vector10.begin(), 0);
    DisplayVector(vector10);

    // Insert 1 element somewhere else
    std::vector<int> vector11{1, 2, 3, 4, 5};
    vector11.insert(vector11.begin() + 1, 0);
    DisplayVector(vector11);

    // Insert repeated element (0 here) somewhere else
    std::vector<int> vector12{1, 2, 3, 4, 5};
    vector12.insert(vector12.begin(), 2, 0);
    DisplayVector(vector12);

    // Insert (copied) elements from another vector (specify range of elements from other vector with iterators)
    std::vector<int> vector13(10);
    vector13.insert(vector13.begin() + 2, vector2.begin() + 1, vector2.begin() + 4);
    DisplayVector(vector13);

    /*
    Random access (constant time). vector13[n] where n is too big has the same possible
    side effects as doing it with an array. vector13.at(n) where n is too big will trigger
    an exception
    */
    std::cout << vector13[0] << " " << vector13.at(0) << std::endl;

    // Like with strings can modify elements with iterators
    std::vector<int> vector14(2);
    *vector14.begin() = 1;
    DisplayVector(vector14);

    // Remove from end with pop_back
    std::vector<int> vector15{1, 2, 3};
    vector15.pop_back();
    DisplayVector(vector15);

    // Remove other elements (less efficient) using erase
    std::vector<int> vector16{1, 2, 3, 4, 5};

    // Single element
    vector16.erase(vector16.begin());
    DisplayVector(vector16);

    // Range of elements
    vector16.erase(vector16.begin() + 1, vector16.begin() + 3);
    DisplayVector(vector16);

    // Can clear vector and check if it's empty
    std::vector<int> vector17(10);
    vector17.clear();
    DisplayVector(vector17);
    std::cout << std::boolalpha << vector17.empty() << std::endl;

    /*
    deque is the same as vector except two things. First, it supports constant time
    push_front and pop_front operations. Second, it doesn't support reserve or
    capacity.
    */
    std::deque<int> deque1(5);
    deque1.push_front(1);
    DisplayDeque(deque1);
    deque1.pop_front();
    DisplayDeque(deque1);

    return 0;
}
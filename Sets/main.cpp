#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

template <typename T>
void DisplayContainer(const T &container)
{
    std::cout << "[ ";
    for (auto itr = container.cbegin(); itr != container.cend(); itr++)
    {
        std::cout << *itr << " ";
    }
    std::cout << "] size = " << container.size() << std::endl;
}

template <typename T>
struct SortDescending
{
    bool operator()(const T &lhs, const T &rhs) const
    {
        return (lhs > rhs);
    }
};

int main()
{
    // Initializing empty set with default comparison of contained elements
    std::set<int> set1;
    DisplayContainer(set1);

    // Initializing empty set with a specified sorting predicate
    std::set<int, SortDescending<int>> set2;
    DisplayContainer(set2);

    // Initializing set with data from container
    std::vector<int> vector1{2, 1, 3};
    std::set<int> set3(vector1.cbegin(), vector1.cend());
    DisplayContainer(set3);

    // Initializing set from same container but sorted differently using predicate
    std::set<int, SortDescending<int>> set4(vector1.cbegin(), vector1.cend());
    DisplayContainer(set4);

    // Initialize set with elements (note that they will be sorted when put into set5)
    std::set<int> set5{2, 1, 3};
    DisplayContainer(set5);

    // Inserting into a set (duplicates ignored)
    set1.insert(1);
    set1.insert(1);
    DisplayContainer(set1);

    // Searching sets (if find was successful, check end()), if we had objects we'd use a dummy object here
    auto itr1{set5.find(1)};
    if (itr1 != set5.end())
    {
        std::cout << "Found: " << *itr1 << std::endl;
    }

    // Fails to compile b/c you cannot modify set elements (b/c they may no longer be sorted correctly)
    // *itr1 = 2;

    auto itr2{set5.find(-1)};
    if (itr2 == set5.end())
    {
        std::cout << "-1 not found" << std::endl;
    }

    // Set removal
    std::set<int> set6{2, 1, 3};
    set6.erase(1);
    DisplayContainer(set6);

    // Can also use iterator of found elements
    set5.erase(itr1);
    DisplayContainer(set5);

    // Or a range of elements
    set5.erase(set5.cbegin(), set5.cend());
    DisplayContainer(set5);

    /*
    Unordered set provides many of the same functions as set except
    that the sorting of internal elements is not guaranteed. Also,
    since it's backed by a hash table versus BST, its operations are
    close to constant time. Can also get stats on the internal table
    such as bucket count and load factor settings.
    */
    std::unordered_set<int> uset1{2, 1, 3};
    DisplayContainer(uset1);

    // C++ also offers ordered and unordered multisets

    return 0;
}
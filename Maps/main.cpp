#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

template <typename T>
void DisplayMap(const T &container)
{
    std::cout << "[ ";
    for (auto itr = container.cbegin(); itr != container.cend(); itr++)
    {
        std::cout << "(" << itr->first << ", " << itr->second << ") ";
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

    // Empty map (default sorting)
    std::map<int, std::string> map1;

    // Map from other map
    std::map<int, std::string> map2(map1);

    // Map with another sorting predicate
    std::map<int, std::string, SortDescending<int>> map3;

    // Add to map with insert which requires a pair which can be made easily with make_pair
    map1.insert(std::make_pair(1, "A"));
    DisplayMap(map1);

    // Add to map with []
    map1[2] = "B";
    DisplayMap(map1);

    // Updating element with []
    map1[2] = "BB";
    DisplayMap(map1);

    // Updating element with at()
    map1.at(1) = "AA";
    DisplayMap(map1);

    // Accessing included elements with []
    std::cout << map1[1] << std::endl;

    // Accessing included elements with at()
    std::cout << map1.at(2) << std::endl;

    /*
    Accessing not included elements with []. Observe that this actually adds a new pair
    to the map. The value of the included pair will be whatever the default constructor
    of the value class is.

    at() will throw an exception provided a key not in the map
    */
    std::cout << map1[3] << std::endl;
    DisplayMap(map1);

    // Searching for element with find (if we had a non primitive key, we could use a dummy object)
    auto itr1{map1.find(1)};
    if (itr1 != map1.end())
    {
        // Yields iterator that references pair
        std::cout << "1 found: " << itr1->first << " " << itr1->second << std::endl;
    }
    auto itr2{map1.find(4)};
    if (itr2 == map1.end())
    {
        std::cout << "4 not found" << std::endl;
    }

    // Removing elements with erase

    std::map<int, std::string> map4;
    map4[1] = "One";
    map4[2] = "Two";
    map4[3] = "Three";
    DisplayMap(map4);
    // Can provide a key
    map4.erase(1);
    DisplayMap(map4);
    // Or an iterator
    map4.erase(map4.find(2));
    DisplayMap(map4);

    /*
    Unordered map provides many of the same functions as set except
    that the sorting of internal elements is not guaranteed. Also,
    since it's backed by a hash table versus BST, its operations are
    close to constant time. Can also get stats on the internal table
    such as bucket count and load factor settings.
    */
    std::unordered_map<int, std::string> umap1;
    umap1[1] = "1";
    DisplayMap(umap1);

    // C++ also provides ordered and unordered multimaps
    return 0;
}
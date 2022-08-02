#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <ctime>
#include <string>
#include <functional>
#include <cctype>

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
struct RangeCounter
{
    size_t count;
    RangeCounter() : count(0) {}
    void operator()(const T &e)
    {
        count++;
    }
};

int main()
{
    std::vector<int> vec1{2017, 0, -1, 42, 10101, 25};

    // Find existing element (will be != to end())
    auto itr1{std::find(vec1.cbegin(), vec1.cend(), -1)};
    if (itr1 != vec1.cend())
    {
        std::cout << *itr1 << std::endl;
    }

    // Find nonexisting element (will be == end())
    itr1 = std::find(vec1.cbegin(), vec1.cend(), 2);
    if (itr1 == vec1.cend())
    {
        std::cout << "2 not found" << std::endl;
    }

    // Store function that checks if something is even (going to be using this multiple times)
    auto is_even{[](int e)
                 { return e % 2 == 0; }};

    // Find element matching predicate - predicate here is lambda function that checks if e is even
    itr1 = std::find_if(vec1.cbegin(), vec1.cend(), is_even);
    if (itr1 != vec1.cend())
    {
        /*
        Use distance to find index of iterator with begin() - note how it works
        with non random access iterators: https://cplusplus.com/reference/iterator/distance/
        */
        std::cout << "Found " << *itr1 << " at index " << std::distance(vec1.cbegin(), itr1) << std::endl;
    }

    std::vector<int> vec2{2017, 0, -1, 42, 10101, 25};

    // Count number of 0s
    auto num_zeros{std::count(vec2.cbegin(), vec2.cend(), 0)};
    std::cout << "0 count: " << num_zeros << std::endl;

    // Count number of even elements
    auto num_even{std::count_if(vec2.cbegin(), vec2.cend(), is_even)};
    std::cout << "even count: " << num_even << std::endl;

    std::vector<int> vec3{2017, 0, -1, 42, 10101, 25, 9, 9, 9};
    std::list<int> ls1{-1, 42, 10101};
    std::list<int> ls2{42, -1, 10101};

    // See if elements in one range exist (contiguously) in another
    auto itr2{std::search(vec3.cbegin(), vec3.cend(), ls1.cbegin(), ls1.cend())};
    if (itr2 != vec3.cend())
    {
        std::cout << std::distance(vec3.cbegin(), itr2) << std::endl;
    }

    itr2 = std::search(vec3.cbegin(), vec3.cend(), ls2.cbegin(), ls2.cend());
    if (itr2 == vec3.cend())
    {
        std::cout << "42,-1,10101 not found contiguously" << std::endl;
    }

    // See if an element repeated n times exist (contiguously) in a range
    itr2 = std::search_n(vec3.cbegin(), vec3.cend(), 3, 9);
    if (itr2 != vec3.cend())
    {
        std::cout << std::distance(vec3.cbegin(), itr2) << std::endl;
    }

    std::vector<int> vec4(5);
    DisplayContainer(vec4);
    // Note fill modifies the vector, needs non const iterators (readonly - use const)
    std::fill(vec4.begin(), vec4.end(), 1);
    DisplayContainer(vec4);

    /*
    time(NULL) returns current time in seconds: https://cplusplus.com/reference/ctime/time/
    srand() sets the random seed: https://cplusplus.com/reference/cstdlib/srand/
    rand() generates a random integer between 0 and some large number: https://cplusplus.com/reference/cstdlib/rand/
    */
    srand(time(NULL));
    std::vector<int> vec5(5);
    DisplayContainer(vec5);
    // Generate fills range from generator (function that takes no parameters, returns things)
    std::generate(vec5.begin(), vec5.end(), rand);
    DisplayContainer(vec5);

    std::vector<int> vec6{2017, 0, -1, 42, 10101, 25, 9, 9, 9};
    // For each calls a function (here a lambda that prints) on each element in a range
    std::for_each(vec6.cbegin(), vec6.cend(), [](int e)
                  { std::cout << e << " "; });
    std::cout << std::endl;

    RangeCounter<int> counter;
    // Can also supply a class that overrides (), this can be used to collect data on range
    std::for_each(vec6.cbegin(), vec6.cend(), counter);
    std::cout << counter.count << std::endl;

    std::vector<int> vec7(vec6.size());
    /*
    Transform applies function to each element and fills another range
    with transformations with results. Hence, we can use const iterators
    on the source range, but a non-const iterator to start the destination
    range.

    Negate int vector
    */
    std::transform(vec6.cbegin(), vec6.cend(), vec7.begin(), [](int e)
                   { return -e; });
    // Observe original vector unchanged, see destination vector filled
    DisplayContainer(vec6);
    DisplayContainer(vec7);

    std::vector<int> vec8(vec6.size(), -1);
    std::vector<int> vec9(vec6.size());
    // plus is a struct that defines operator() that adds 2 elements (https://cplusplus.com/reference/functional/plus/)
    std::transform(vec6.cbegin(), vec6.cend(), vec8.cbegin(), vec9.begin(), std::plus<int>());
    // Observe original vectors unchanged, see destination vector filled
    DisplayContainer(vec6);
    DisplayContainer(vec8);
    DisplayContainer(vec9);

    // To see transform's use with strings see Characters_and_Strings

    std::list<int> ls3{1, 2, 3};
    std::vector<int> vec10(ls3.size());
    // Const iterators are ok from source, need non const iterator for destination
    std::copy(ls3.cbegin(), ls3.cend(), vec10.begin());
    DisplayContainer(ls3);
    DisplayContainer(vec10);

    // Can copy some elements that satisfy predicate
    std::vector<int> vec11(ls3.size());
    std::copy_if(ls3.cbegin(), ls3.cend(), vec11.begin(), is_even);
    DisplayContainer(vec11);

    std::vector<int> vec12{1, 2, 2, 3};
    // remove modifies the range, must be non-const iterators
    auto new_end{std::remove(vec12.begin(), vec12.end(), 2)};
    // note that remove doesn't actually remove - it moves removed elements to the end
    std::cout << std::distance(vec12.begin(), new_end) << std::endl;
    DisplayContainer(vec12);
    // therefore to actually remove the elements, we remove after the new end (which specifies
    // new end of elements we wanted to keep) - erase from new end to end()
    vec12.erase(new_end, vec12.end());
    DisplayContainer(vec12);

    // Can also remove based on predicate with remove_if like copy_if, count_if, etc.

    std::vector<int> vec13{1, 2, 2, 3};
    // To replace, use non const iterators
    std::replace(vec13.begin(), vec13.end(), 2, 5);
    DisplayContainer(vec13);

    std::vector<int> vec14{1, 2, 4, 3};
    // replace all even elements with 0
    std::replace_if(vec14.begin(), vec14.end(), is_even, 0);
    DisplayContainer(vec14);

    std::vector<int> vec15{3, 1, 4, 2, 3};
    // sort is in place (use non const iterators) - use stable_sort to ensure stability
    std::sort(vec15.begin(), vec15.end());
    DisplayContainer(vec15);

    std::vector<int> vec16{3, 1, 4, 2, 3};
    // sort descending
    // If defining a custom predicate, it must specify a strick weak ordering, see:
    // https://cplusplus.com/reference/algorithm/sort/
    // https://stackoverflow.com/a/19757240
    // https://stackoverflow.com/a/981299
    std::sort(vec16.begin(), vec16.end(), std::greater<int>());
    DisplayContainer(vec16);

    // Can use unique to remove adjacent duplicates (useful after a sort)
    new_end = std::unique(vec15.begin(), vec15.end());
    // Note that, like remove doesn't actually remove, moves duplicates to the end
    DisplayContainer(vec15);
    // remove duplicates from the end
    std::cout << std::distance(vec15.begin(), new_end);
    vec15.erase(new_end, vec15.end());
    DisplayContainer(vec15);

    // note this doesn't get rid of nonadjacent duplicates
    std::vector<int> vec17{3, 1, 4, 3, 2};
    new_end = std::unique(vec17.begin(), vec17.end());
    DisplayContainer(vec17);
    std::cout << std::boolalpha << (new_end == vec17.end()) << std::endl;

    // also supplies bool binary search
    std::cout << std::binary_search(vec15.cbegin(), vec15.cend(), 3) << " " << std::binary_search(vec15.cbegin(), vec15.cend(), 5) << std::endl;

    std::vector<int> vec18{3, 1, 4, 3, 2};
    // mutates so use non const iterators (elements satisfying predicate are moved to left partition)
    std::partition(vec18.begin(), vec18.end(), is_even);
    DisplayContainer(vec18);

    // stable_partition maintains order within partitions, but is slower

    std::vector<int> vec19{1, 2, 3, 3, 6};
    auto min_pos{std::lower_bound(vec19.cbegin(), vec19.cend(), 5)};
    auto max_pos{std::upper_bound(vec19.cbegin(), vec19.cend(), 5)};
    // This means we can add a 5 by inserting at only 4 (before 6)
    std::cout << std::distance(vec19.cbegin(), min_pos) << " " << std::distance(vec19.cbegin(), max_pos) << std::endl;
    min_pos = std::lower_bound(vec19.cbegin(), vec19.cend(), 1);
    max_pos = std::upper_bound(vec19.cbegin(), vec19.cend(), 1);
    // This means we can add a 1 by inserting at 0 or at 1 (before or after existing 1)
    std::cout << std::distance(vec19.cbegin(), min_pos) << " " << std::distance(vec19.cbegin(), max_pos) << std::endl;
    min_pos = std::lower_bound(vec19.cbegin(), vec19.cend(), 3);
    max_pos = std::upper_bound(vec19.cbegin(), vec19.cend(), 3);
    // This means we can add a 3 by inserting at 2, 3, or 4 (before or after at either of existing 3s)
    std::cout << std::distance(vec19.cbegin(), min_pos) << " " << std::distance(vec19.cbegin(), max_pos) << std::endl;

    return 0;
}

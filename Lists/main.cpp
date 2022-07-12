#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>

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

bool SortPredicateDescending(const int &lhs, const int &rhs)
{
    return lhs > rhs;
}

class Record
{
private:
    std::string name;
    std::string phone_number;
    // Why do we store this string? See discussion above constructor
    std::string display;

public:
    // Make this a friend so it can access private member phone_number
    friend bool SortOnPhoneNumber(const Record &lhs, const Record &rhs);

    /*
    Q1: Why take const string& not string_view? Because we cannot easily create display
    member with string_views as string_view cannot be concatenated with a string or
    const char (see: https://stackoverflow.com/a/47735624). Thus, we would have to create
    a string copy anyway if we were say taking a literal (as we do when we construct
    Records in main code) through a string_view because that string_view would have to
    be turned into a string to do concatenation. const string& will take the temporarily
    created string to accomodate the literal as reference.

    Q2: Why do we store display as a member? Because, if we were to create it locally in
    our const char* operator, then when we call c_str on a local variable, it will
    become invalidated upon function return as all it does is provide a pointer to
    the contents of a string (see: https://stackoverflow.com/a/27627466)
    */
    Record(std::string_view n, std::string_view pn) : name(n), phone_number(pn) {
        display = "[" + name + " " + phone_number + "]";
    }

    // Defines how list::remove (and Record equality in general) will work
    bool operator==(const Record &other) const
    {
        return this->name == other.name;
    }

    // Defines how list::sort works without a passed predicate function
    bool operator<(const Record &other) const
    {
        return this->name < other.name;
    }

    // See discussion above
    operator const char *() const
    {
        return display.c_str();
    }
};

bool SortOnPhoneNumber(const Record &lhs, const Record &rhs)
{
    return lhs.phone_number < rhs.phone_number;
}

int main()
{
    // Creating lists

    // Empty list
    std::list<int> list1;
    // Won't compile b/c list doesn't support printing
    // std::cout << l   ist1 << std::endl;
    DisplayContainer(list1);

    // List with specific elements
    std::list<int> list2{1, 2, 3, 4, 5};
    DisplayContainer(list2);

    // List with 10 zeros
    std::list<int> list3(10);
    DisplayContainer(list3);

    // List with 10 90s
    std::list<int> list4(10, 90);
    DisplayContainer(list4);

    // List from another list
    std::list<int> list5(list4);
    DisplayContainer(list5);

    /*
    One cannot instantiate a list from the subset of another list because you
    cannot perform + n operations on list iterators as they are bidirectional
    iterators (https://cplusplus.com/reference/iterator/BidirectionalIterator/).
    You can do +/- n operations on vector iterators as they are random access
    iterators (https://cplusplus.com/reference/iterator/RandomAccessIterator/).
    */
    // std::list<int> list6(list2.cbegin() + 1, list2.cbegin() + 4);

    // List from subset of a vector
    std::vector<int> vector1{1, 2, 3, 4, 5};
    std::list<int> list7(vector1.cbegin() + 1, vector1.cbegin() + 4);
    DisplayContainer(list7);

    // Warning with initializer list, this creates a list with 10, not a list of 10 0s
    std::list<int> list8{10};
    DisplayContainer(list8);

    // Add to front, back
    std::list<int> list9(5, 0);
    list9.push_front(1);
    list9.push_back(2);
    DisplayContainer(list9);

    // Add at middle (using an iterator)

    // Add 1 element
    std::list<int> list10(5, 0);
    auto insert_itr{list10.cbegin()};
    insert_itr++;
    insert_itr++;
    list10.insert(insert_itr, 2);
    DisplayContainer(list10);

    // Add repeated element
    std::list<int> list11(5, 0);
    insert_itr = list11.cbegin();
    insert_itr++;
    insert_itr++;
    list11.insert(insert_itr, 2, 1);
    DisplayContainer(list11);

    // Insert from another container (list, vector, etc.)
    std::list<int> list12(5, 0);
    insert_itr = list12.cbegin();
    insert_itr++;
    insert_itr++;
    list12.insert(insert_itr, vector1.cbegin(), vector1.cend());
    DisplayContainer(list12);

    // Removal

    // Remove front, back
    std::list<int> list13{1, 2, 3, 4, 5};
    list13.pop_back();
    list13.pop_front();
    DisplayContainer(list13);

    // Remove 1 element from middle
    std::list<int> list14{1, 2, 3, 4, 5};
    auto rmv_itr{list14.cbegin()};
    rmv_itr++;
    rmv_itr++;
    list14.erase(rmv_itr);
    DisplayContainer(list14);

    // Remove multiple elements from middle
    std::list<int> list15{1, 2, 3, 4, 5};
    auto rmv_itr2{list15.cbegin()};
    rmv_itr2++;
    rmv_itr = list15.cbegin();
    rmv_itr++;
    rmv_itr++;
    rmv_itr++;
    list15.erase(rmv_itr2, rmv_itr);
    DisplayContainer(list15);

    // Can clear list
    list15.clear();
    DisplayContainer(list15);
    std::cout << std::boolalpha << list15.empty() << std::endl;

    /*
    Reversing list, Rao lesson 18 unclear as to why not to use algorithm reverse.
    Could have something to do with iterator invalidation, see:
    https://stackoverflow.com/questions/16904454/what-is-iterator-invalidation
    https://stackoverflow.com/questions/6438086/iterator-invalidation-rules-for-c-containers
    https://thispointer.com/stdvector-and-iterator-invalidation/
    */
    std::list<int> list16{1, 2, 3, 4, 5};
    list16.reverse();
    DisplayContainer(list16);

    /* Sorting list, Rao lesson 18 is unclear about why to use list::sort versus algorithm
    sort, algorithm sort requires random access:
    https://stackoverflow.com/questions/10652674/sorting-stdlists-using-stdsort

    More info here on how list::sort works: https://stackoverflow.com/a/1717830
    */
    std::list<int> list17{2, 1, 4, 3, 5};
    list17.sort();
    DisplayContainer(list17);

    // Sorts in descending order
    std::list<int> list18{2, 1, 4, 3, 5};
    list18.sort(SortPredicateDescending);
    DisplayContainer(list18);

    // Sorting objects - uses operator< defined in Record
    std::list<Record> list19;
    list19.push_back(Record("B C", "123"));
    list19.push_back(Record("A B", "789"));
    list19.push_back(Record("A C", "456"));
    list19.sort();
    DisplayContainer(list19);

    // If we want to override, use another function as before
    list19.sort(SortOnPhoneNumber);
    DisplayContainer(list19);

    // Remove finds an element and removes it
    std::list<int> list20{1, 2, 3, 4, 5};
    list20.remove(3);
    DisplayContainer(list20);

    /*
    Since Records operator== works on names, if we want to remove a Record,
    just create a dummy Record that will match it based on operator== (which
    in this case just needs a matching name)
    */
    list19.remove(Record("A B", ""));
    DisplayContainer(list19);

    // C++ also supports a singly linked list in forward_list: https://cplusplus.com/reference/forward_list/forward_list/

    return 0;
}
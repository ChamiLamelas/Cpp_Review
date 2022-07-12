#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <functional>

int main()
{

    // Constructs empty stack
    std::stack<int> stack1;

    // Changes backing container to vector instead of deque
    std::stack<int, std::vector<int>> stack2;

    // Can copy over elements from another stack
    std::stack<int> stack3(stack1);

    /*
    Can construct stack from vector, deque but seems to defeat the purpose as those can be used
    as a stack. To do so, it seems like the backing container of stack must match the container
    you're trying to copy from (can't find this explictly in Rao, online, or in docs).
    */

    // Add to stack with push
    stack1.push(2);
    stack1.push(3);

    // View top with top, size with size
    std::cout << stack1.top() << " " << stack1.size() << std::endl;

    // Remove top with pop (note it is void), check empty with empty
    stack1.pop();
    std::cout << std::boolalpha << stack1.empty() << std::endl;

    // Cannot create iterators to see other contents of a stack (to match ADT)

    // like stack can change backing container or copy from another queue
    std::queue<int> queue1;

    // add to end with push
    queue1.push(4);
    queue1.push(5);

    // See front and back, size
    std::cout << queue1.front() << " " << queue1.back() << " " << queue1.size() << std::endl;

    // Remove front with pop
    queue1.pop();
    std::cout << queue1.empty() << std::endl;

    // Construct empty priority queue (heap backed), will use default operator< for sorting (like Java)
    std::priority_queue<int> pq1;

    // Add with push
    pq1.push(10);
    pq1.push(5);
    pq1.push(-1);
    pq1.push(20);

    /*
    Here we see that priority_queue functions like a max priority queue
    because top is always the highest valued element with however
    the sorting is defined (recall default is operator<)
    */
    while (!pq1.empty())
    {
        std::cout << pq1.top() << " ";
        pq1.pop();
    }
    std::cout << std::endl;

    /*
    If we want to have a minimum priority queue, use opposite of default
    sort which is really functional::less(x,y) which is a struct that
    overloads operator() to return x<y. The opposite is functional::greater(x,y)
    which is a struct that overloads operator() to return x>y. Priority queue
    works by saying if Compare(x,y) is true, x gets put lower than y in priority
    queue. If Compare=functional::less, then x gets put lower than y if x<y.
    If Compare=functional::less, then x gets put lower than y if x>y.

    Including functional::greater here is just like using our SortDescending
    struct from Vector_and_Deque, Lists, Sets, and Maps.
    */
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq2;

    pq2.push(10);
    pq2.push(5);
    pq2.push(-1);
    pq2.push(20);

    while (!pq2.empty())
    {
        std::cout << pq2.top() << " ";
        pq2.pop();
    }
    std::cout << std::endl;

    return 0;
}
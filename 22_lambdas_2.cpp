#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <list>
#include <functional>

/******

    A program to use lambdas with STL containers and User defined Classes.
    It also shows how to use the std::function() to point to a lambda function.

******/

class Height    {
public:
    int _feet;
    int _inches;

public:
    Height(int feet = 0, int inches = 0): _feet(feet), _inches(inches) {
    }

    void print() {  std::cout << _feet << "\'" << _inches << "\""; }
    
    int ft() { return _feet; }
};

std::function<int(int, int)> larger()
{
    std::cout << "inside larger" << std::endl;

    return [] (int x, int y) -> int { return ( x > y ? x : y); };
} 

int main() {

    std::vector<int> vals = { 10, 5, 23, 19, 9, 20 };

    int biggest = std::numeric_limits<int>::min();

/// Find the largest element in the vector

    // Use a lambda to set 'biggest' to the largest value in the vector.
    // The local variables, 'biggest' is passed by reference.

    std::for_each( vals.begin(), vals.end(),
        [&](int val) { if( val > biggest ) biggest = val; }
    );

    std::cout << "Largest value: " << biggest << std::endl;

/// Replace the negative elements in the list with a zero, using a lambda expression.

    std::list <int> nums = { 20, -34, 55, -1090, 600, -780, -5 };

    std::cout << "\nOriginal nums list:" << std::endl;
    for(auto i:nums)
        std::cout << i << ", "; std::cout << std::endl;

    std::replace_if( nums.begin(), nums.end(), 
        [&](int n) { return (n<0); }, 0 );

    std::cout << "nums list post replacing negative numbers:" << std::endl;
    for(auto i:nums)
        std::cout << i << ", "; std::cout << std::endl;

/// Sort the heights using a lambda function

    std::vector<Height> heights = { {5, 23}, {2, 60}, {0, 100}, {3,36}, {2, 20}, {0, 200} };

    std::cout << "Heights, Original list:"  << std::endl;

    for(auto h:heights) {
        h.print();
        std::cout << ", ";
    }

    std::sort( heights.begin(), heights.end(), 
        [] (const Height & i, const Height & j) { return ( ((i._feet * 12) + i._inches) < ((j._feet * 12) + j._inches) ); });

    std::cout << "\nHeights, Post sort:"  << std::endl;

    for(auto h:heights) {
        h.print();
        std::cout << ", ";
    }

    std::cout << std::endl;

/// Use the lambda to point to the function wrapper created using std::function 

    int i=10, j=20;

    // Function that accepts two integers and returns an integer
    // This though is an overhead since the lambda can be called directly, without binding it to the wrapper.

    std::function<int(int,int)> bigger = [] (int x, int y) { return ( x > y ? x : y); };

    std::cout << "bigger: " << bigger(i,j) << std::endl;  
    std::cout << "bigger: " << bigger(200, 100) << std::endl;  

    auto l = larger();

    std::cout << "larger: " << l(i,j) << std::endl;  
    std::cout << "larger: " << l(200, 100) << std::endl;  
    std::cout << "larger: " << l(200, 1000) << std::endl;  

    return 0;
}

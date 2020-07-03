#include <iostream>
#include <utility>

#include <string>
#include <map>
#include <list>
#include <typeinfo>

/******
    The program demonstrates the use of the 'decltype'
    'decltype' allows the compiler to find the type of an expression.
******/

using IntToStrPair = std::pair<int, std::string>;
using IntToStrMap = std::map <int, std::string>;

void PRINTMAP(std::map<int, std::string> & myMap)
{
    std::map<int, std::string>::iterator iter = myMap.begin();

    // decltype creates rit as the same type of iter => std::map<int, std::string>::iterator
    decltype(iter) rit = myMap.end(); 

    --rit; // Traverse to the last element, one before myMap.end()
        
    std::cout << "\nTraverse Reverse:" << std::endl;

    do{
        std::cout << "[" << rit->first << ", " << rit->second << "], ";
    } while ( rit-- != myMap.begin() );

    std::cout << std::endl;
}

// Like the lambdas the new function declaration syntax allows the return type to be after the parameters
template <typename T1, typename T2>
auto product(T1 x, T2 y) -> decltype(x * y)     // the decltype allows the return type to be of type T1*T2
{
    return (x * y);
}


int main()
{
	IntToStrMap nTostrMap;
	nTostrMap.insert( std::make_pair(1, "One") );
	nTostrMap.insert( std::make_pair(5, "Five") );
	nTostrMap.insert( std::make_pair(3, "Three") );
	nTostrMap.insert( std::make_pair(2, "Two") );

	PRINTMAP(nTostrMap);

///// decltype

    int x = -10, y = -10;

    auto sum = [](int x, int y) { return (x + y); };
    std::cout << "\nsum: " << sum(x,y) << std::endl;

    decltype(sum) sum1 = sum;
    std::cout << "sum1: " << sum(abs(x), abs(y)) << std::endl;
   
    std::cout << "\nproduct(3 * 4):" << product(3, 4) << ", typeid(product(3, 4)): " << typeid(product(3, 4)).name() << std::endl; 
    std::cout << "product(3 * 4):" << product(3, 4.5) << ", typeid(product(3, 4.5)): " << typeid(product(3, 4.5)).name() << std::endl; 
    std::cout << "product(3 * 4):" << product(3.5, 4.5) << ", typeid(product(3.5, 4.5)): " << typeid(product(3.5, 4.5)).name() << std::endl; 

    return 0;
}


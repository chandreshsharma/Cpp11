#include <iostream>
#include <utility>

#include <string>
#include <map>
#include <list>

/******

The program demonstrates the use of the 'auto' type and 'for each' in C++ 11
The 'auto' type automatically derives the type based on the RHS variable.

'for each' allows to work on each item of the container, and works on any container that has a begin() and end()

Reference: cppreference.com

for ( range_declaration : range_expression ) loop_statement

    range_declaration - a declaration of a named variable, whose type is the type of the element of the sequence represented by range_expression, or a reference to that type. 
                        Often uses the auto specifier for automatic type deduction
    range_expression  - any expression that represents a suitable sequence (either an array or an object for which begin and end member functions or free functions are defined) 
                        or a braced-init-list.
******/

using IntToStrPair = std::pair<int, std::string>;
using IntToStrMap = std::map <int, std::string>;

void PRINTMAP(std::map<int, std::string> & myMap)
{
//    for(std::map<int, std::string>::iterator i = myMap.begin(); i != myMap.end(); ++i)

	std::cout << "\nTraversing map using auto" << std::endl;
    for(auto i = myMap.begin(); i != myMap.end(); ++i)		///@@@CS: Use 'auto' instead of the entire iterator definition
	{
        std::cout << "[" << i->first << ", " << i->second << "], ";
	}
    std::cout << std::endl;

    // Range based for loop.
    // For each element fetched as variable pr, when iterating the container myMap
	std::cout << "\nTraversing map using for each and auto" << std::endl;
	for(auto pr: myMap)
	{
        std::cout << "[" << pr.first << ", " << pr.second << "], ";
	}
    std::cout << std::endl;

	std::cout << "\nTraversing map using const reference" << std::endl;
	for(const IntToStrPair & p: myMap)
	{
        std::cout << "[" << p.first << ", " << p.second << "], ";
	}
    std::cout << std::endl;
}



int main()
{
	IntToStrMap nTostrMap;
	nTostrMap.insert( std::make_pair(1, "One") );
	nTostrMap.insert( std::make_pair(5, "Five") );
	nTostrMap.insert( std::make_pair(3, "Three") );
	nTostrMap.insert( std::make_pair(2, "Two") );

	PRINTMAP(nTostrMap);

	std::list<float> fLis;
    
	fLis.push_back(1.2);		
	fLis.push_back(3.45);		
	fLis.push_back(6.78);		
	fLis.push_back(9.012);

	std::cout << std::endl;

	for(auto val: fLis) std::cout << val << ", ";
	std::cout << std::endl;


    // Using std::initializer_list<> in for each
    // The std::initializer_list<> defines the begin() and end() methods, so the for each can use the initializer_list

    std::cout <<  "\nfor each(...) using std::initializer_list<>:  " << std::endl;
    for(auto i: {1, 2, 3, 4, 5})
        std::cout << i << ", "; std::cout << std::endl;

    std::initializer_list<std::string> strIL {"A", "Initializer", "list", "of", "strings" };

    for(auto s : strIL)
        std::cout << s << " "; std::cout << std::endl;
    
    return 0;
}


#include <iostream>
#include <utility>

#include <string>
#include <map>
#include <list>

/******

The program demonstrates the use of the 'auto' type and 'for each' in C++ 11
The 'auto' type automatically derives the type based on the RHS variable.

'for each' allows to work on each item of the container, and works on any container that has a begin() and end()

******/

//typedef std::pair<int, std::string> IntToStrPair;
//typedef std::map <int, std::string> IntToStrMap;
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

	std::cout << "\nTraversing map using for each and auto" << std::endl;

	for(auto pr: myMap)
	{
        std::cout << "[" << pr.first << ", " << pr.second << "], ";
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
}


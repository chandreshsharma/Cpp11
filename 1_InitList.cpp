#include <iostream>
#include <string>

#include <list>
#include <set>
#include <vector>
#include <map>
#include <functional>   // for std::less<>


/********************************************************************************************************************
 Program to see the functionality of an initializer list.

// The C++ 11 standard extends the initializer list beyond the array, and allows initializing the standard containers,
// like vector, list, set using initializer list.

// The program also introduces 'type alias' and 'alias template' to refer a previous defined type OR family of types

References: cppreference.com

A 'type alias' introduces a name which can be used as a synonym for the type denoted by type-id.
It does not introduce a new type and it cannot change the meaning of an existing type name.
There is no difference between a type alias declaration and typedef declaration.

An 'alias template' is a template which, is equivalent to the result of substituting the template arguments
of the alias template for the template parameters in the type-id.
********************************************************************************************************************/




#if 0   // using typedef
    typedef std::pair<int, std::string> IntToStrPair;
#else
    // Changing to the new syntax for 'type alias' available in C++ 11

    using IntToStrPair = std::pair<int, std::string>;
#endif


/******************** Main ************************/

template <class T>
void PRINT(T & cont);


template <class T>
using Vec = std::vector<T>;

template <class T1, class T2>       // alias template
using Map = std::map<T1, T2, std::less<T1> >;

template <class T1, class T2>       // alias template
using MapRev = std::map<T1, T2, std::greater<T1> >;     // Create a Reverse Map. 
                                                        // A alias template is more useful in scenario when the template arguments are not the default ones.

using IntToStrMap = Map<int, std::string>;          // type alias for substituted template type
using IntToStrMapRev = MapRev<int, std::string>;    // type alias for substituted template type

void PRINTMAP(IntToStrMap & myMap);
void PRINTMAPREV(IntToStrMapRev & myMap);

int main()
{
	std::set<std::string> strSet = {"abc", "defg", "hijkl", "mnopqr", "stuvwxyz"}; // default syntax

    Vec<int> intVec = {10, 20, 30, 50};     // Vec defined as a alias template

    using FloatList = std::list<float>;     // alias type
    FloatList fList = {1.2, 2.34, 45.67, 789.10};

    IntToStrMap intToStrMap = { {2,"Two"}, {3,"Three"}, {1,"One"} };
    IntToStrMapRev intToStrMapRev = { {2,"Two"}, {3,"Three"}, {1,"One"} };

    PRINT(intVec);
	PRINT(fList);
	PRINT(strSet);

	PRINTMAP(intToStrMap);
	PRINTMAPREV(intToStrMapRev);

	return 0;
}


/************** Template Function Definitions ******/

template <class T>
void PRINT(T & cont)
{
	typename T::iterator i = cont.begin(); // typename instructs the compiler to treat the statement as a declaration

	/*
	   COMPILER ERROR:

	   1_initializer_list.cpp: In function ‘void PRINT(T&)’:
	   1_initializer_list.cpp:19:6: error: need ‘typename’ before ‘T:: iterator’ because ‘T’ is a dependent scope
	   for(T::iterator i = cont.begin(); i != cont.end(); ++i)
	   ^
	 */

	for(;i != cont.end(); ++i)
		std::cout << *i << ", ";
   
	std::cout << std::endl;
}

void PRINTMAP(IntToStrMap & myMap)
//void PRINTMAP(std::map<int, std::string> & myMap)
{
	for(std::map<int, std::string>::iterator i=myMap.begin(); i != myMap.end(); ++i)
		std::cout << "[" << i->first << ", " << i->second << "], "; 
	
	std::cout << std::endl;
}

void PRINTMAPREV(IntToStrMapRev & myMap)
{
	for(std::map<int, std::string>::iterator i=myMap.begin(); i != myMap.end(); ++i)
		std::cout << "[" << i->first << ", " << i->second << "], "; 
	
	std::cout << std::endl;
}

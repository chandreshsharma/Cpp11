#include <iostream>
#include <string>

#include <list>
#include <set>
#include <vector>
#include <map>


/********************************************************************************************************************
 Program to see the functionality of an initializer list.

// The C++ 11 standard extends the initializer list beyond the array, and allows initializing the standard containers,
// like vector, list, set using initializer list.

********************************************************************************************************************/




template <class T>
void PRINT(T & cont);

void PRINTMAP(std::map<int, std::string> & myMap);

typedef std::pair<int, std::string> IntToStrPair ;


/******************** Main ************************/

int main()
{
	std::vector<int> intVec = {10, 20, 30, 50};
	std::list<float> fList = {1.2, 2.34, 45.67, 789.10};
	std::set<std::string> strSet = {"abc", "defg", "hijkl", "mnopqr", "stuvwxyz"};
	std::map<int, std::string> intToStrMap = { {1,"One"}, {2,"Two"}, {3,"Three"} };

	
    PRINT(intVec);
	PRINT(fList);
	PRINT(strSet);

	PRINTMAP(intToStrMap);

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


void PRINTMAP(std::map<int, std::string> & myMap)
{
	for(std::map<int, std::string>::iterator i=myMap.begin(); i != myMap.end(); ++i)
		std::cout << "[" << i->first << ", " << i->second << "], "; 
	
	std::cout << std::endl;
}

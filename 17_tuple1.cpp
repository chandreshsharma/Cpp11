#include <iostream>
#include <tuple>
#include <functional>   // For std::ref
#include <utility>

/***********

Program to understand the usage of the C++ 11 Tuple class.

A tuple in C++ is similar a 'database record' that stores values against fields. Each of the field is defined of a specific data type.

std::tuple <datatype element1, datatype element2, ..., datatype element n>

std::get():
===========
    std::get<index>(std::tuple) // Fetches a specific element from a tuple

function template:
    template <size_t S, class... T>
    typename tuple_element< S, tuple<T...> >::type& get(tuple<T...>& t) noexcept;

std::make_tuple():
================
    template<class... T>
    tuple<T...> make_tuple (T&&... args);

Creates a std::tuple object containing the elements of the data type(s) specified.

std::tie():
==========
    template<class... T>
    tuple<T&...> tie (T&... args) noexcept;
    
Creates a tuple with each argument is a reference to the corresponding tuple element.
std::ignore is used in case the value of a tuple element isn't needed.

std::tuple_cat():
=================
    template <class... Tup>
    tuple<T...> tuple_cat (Tuples&&... t);

Creates a tuple combining elements from each of the tuples passed.
***********/

using namespace std;


using EmpRecord = tuple <unsigned long, std::string, std::pair<std::string, std::string> >; // Declare an employee record

using PairOfStrings = std::pair<std::string, std::string>;

void print(EmpRecord emp)
{
    // The std::get access the specific record in the tuple.

    std::cout   << "Emp ID: " << std::get<0>(emp) << ", Name: " 
                << std::get<1>(emp) << ", Phone1: " << std::get<2>(emp).first 
                << ", Phone2: " << std::get<2>(emp).second << std::endl;
}

void printValues(long int id, std::string name, PairOfStrings phones)
{
    std::cout   << "Emp ID: " << id << ", Name: " << name 
                << ", Phone1: " << phones.first << ", Phone2: " << phones.second << std::endl;
}


#if __cplusplus > 201103L  // Verify compiler version supports C++ 14

// Selecting a tuple element by data type is supported in the C++ 14 standard

void printByType(EmpRecord emp)
{
    std::cout   << "Emp ID: " << std::get<unsigned long>(emp) << ", Name: " 
                << std::get<std::string>(emp) << ", Phone1: " << std::get<std::pari>(emp).first 
                << ", Phone2: " << std::get<2>(emp).second << std::endl;
}

#endif

int main()
{
// A tuple in C++ 11 is similar to a database record, values are stored against data types.

    std::tuple <std::string, int, bool> t("Sample Tuple", 100, true);

// Values can be retrieved from a tuple using the std::get() function.

    std::cout   << "first:" << std::get<0>(t) 
                <<", second:" << std::get<1>(t) 
                << ", third:" << std::get<2>(t) << std::endl;
    
// The std::get() function returns a reference, so it can be used to change the value of the index.

    std::get<0>(t) = "First Tuple";
    std::cout   << "first:" << std::get<0>(t) 
                <<", second:" << std::get<1>(t) 
                << ", third:" << std::get<2>(t) << std::endl;
    
    EmpRecord emp1 = make_tuple(1, "Sam", make_pair("+91 9988776655", "080 22334455"));
    print(emp1);

// Update element value
// To change a record, fetch a reference to the element and update the element value

    std::pair<std::string, std::string> & p = std::get<2>(emp1);    // Get index 2 of the tuple
    p.second = "080 11223344"; 
    print(emp1);

    EmpRecord emp2 = make_tuple(2, "Will", make_pair("+91 987654321", "080 76543210"));
    print(emp2);

    // std::tuple overloads the comparison operator, compares the records lexicographycally
    std::cout << "The larger record is:" << std::endl;
    if(emp2 > emp1)
        print(emp2);
    else
        print(emp1);

// Create a copy
// A copy of a tuple can be created using the assignment operator or a default copy constructor
    
    EmpRecord empDef = make_tuple(0xFFFF, "NA", make_pair("-", "-"));

    EmpRecord def1(empDef);         // Create copy using Copy Constructor
    EmpRecord def2; def2 = empDef;  // Create copy using assignment operator

    std::cout << "Default Employee Records: " << std::endl;
    print(def1);
    print(def2);

#if __cplusplus > 201103L   // Verify compiler version supports C++ 14

    // Selecting a tuple element by data type is supported in the C++ 14 standard   

    // Values inside a tuple can also be accessed using type inside std::get rather than index.
    EmpRecord auto emp3 = make_tuple(3, "Roger", make_pair("+91 9191919191", "080 28282828"));
    printByType(emp3);
    
#endif  

// lvalue reference
// A tuple allows the elements to be of type lvalue references.
// So you can create a tuple which has lvalue reference to another tuples elements.
// NOTE: The other containers in C++ STL dont store references.

    PairOfStrings tmp = make_pair("String 1", "String 2");
    std::tuple<std::string &, std::string&> tup(tmp.first, tmp.second);

    std::cout << "Original Tuple: " << std::get<0>(tup) << ", " << std::get<1>(tup) << std::endl;
    std::get<0>(tup) = "First String";

    std::cout << "After updating tuple, Pair  : " << tmp.first << ", " << tmp.second << std::endl;
    std::cout << "After updating tuple, Tuple : " << std::get<0>(tup) << ", " << std::get<1>(tup) << std::endl;

    tmp.second = "Second String";

    std::cout << "After updating pair, Pair  : " << tmp.first << ", " << tmp.second << std::endl;
    std::cout << "After updating pair, Tuple : " << std::get<0>(tup) << ", " << std::get<1>(tup) << std::endl;

// std::tie provides such a functionality
// std::tie creates a tuple of lvalue references for each of fields in the tuple.
// In case a field isnt required it can be passed as std::ignore. std::ignore ignores the values assigned to it.

    long int tmpID = 0;
    std::string tmpName = {};
    PairOfStrings tmpPhones = {};
#if 0
    std::make_tuple(std::ref(tmpID), std::ref(tmpName), std::ref(tmpPhones));   // std::ref is defined in <functional>
#else
    // Equivalent to std::make_tuple(ref(tmpID), ref(tmpName), ref(tmpPhones));
    std::tie(tmpID, tmpName, tmpPhones) = emp1;     // Each of the members would be assigned the values inside the tuple
#endif
    printValues(tmpID, tmpName, tmpPhones);

    // Change the reference of the values besides the last value
    std::tie(tmpID, tmpName, std::ignore) = emp2;
    std::cout << "After reassignment, Emp ID: " << tmpID << ", Name: " << tmpName << std::endl;

// Concatenate tuples
// std::tuple_cat() can be used to concatenate tuples.

    auto concTup = std::tuple_cat(tmp, emp1);   // A tuple with fields (string, string, 
                                                //          unsigned long, std::string, std::pair<std::string, std::string>)
   
    auto size = std::tuple_size<decltype(concTup)>::value; 
    std::cout << "Number of fields in new tuple: " << size << std::endl;

#if 0
    // The get function accepts only a compile time constant.
    // The attempt here was to fetch a constexpr using a lambda function. This way we can have an iterator
    // for the tuple fields

    for(int i=0; i < size; ++i)
    {
        constexpr auto index = [](int x) { return x; };
        std::cout << "Element " << i << ": " << std::get<index(i)>(concTup) << ", ";
    }
    std::cout << std::endl;
#endif
    
    return 0;
}

#include <iostream>

#include <chrono>
#include <tuple>

/***********

A program with some examples of using tuples


***********/

// function needs to return a large number of data tuples
using TimeTuple = std::tuple<int, long, long long, long long>;

TimeTuple retTimeVals(int const & seconds)
{   
//    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(millSec);
    std::chrono::seconds sec(seconds);
    std::chrono::milliseconds millSec = sec;        //36000 milliseconds
    std::chrono::microseconds microSec = millSec;   //36000000 microseconds
    std::chrono::nanoseconds nanoSec = microSec;    //36000000000 nanoseconds

#if defined(DEBUG)
    std::cout << "seconds:      " << sec.count() << std::endl;
    std::cout << "milliseconds: " << millSec.count()  << std::endl;
    std::cout << "microseconds: " << microSec.count() << std::endl;
    std::cout << "nanoseconds:  " << nanoSec.count() << std::endl;
#endif

    // count() returns the number of elements stored in the duration.
    return std::make_tuple(sec.count(), millSec.count(), microSec.count(), nanoSec.count()); 
}

using EmpTuple = std::tuple<std::string, int, std::string>;

void printEmp(EmpTuple emp)
{
    std::cout << std::get<0>(emp) << ", " << std::get<1>(emp) << ", " << std::get<2>(emp) << std::endl;
}

int main()
{
    unsigned long long secs, milliSec, microSec, nanoSec;

// Using tuple instead of a struct

    // Since std::tie passes the arguments as a reference, each of the values now hold
    // the elements stored in the tuple.
    // Using a tuple in this way prevents creating a struct, for a single use.

    std::tie(secs, milliSec, microSec, nanoSec) = retTimeVals(10);

    std::cout << "seconds:      " << secs << std::endl;
    std::cout << "milliseconds: " << milliSec  << std::endl;
    std::cout << "microseconds: " << microSec << std::endl;
    std::cout << "nanoseconds:  " << nanoSec << std::endl;

// swapping the value of 2 tuples.

    //std::tuple provides the ability to swap 2 tuples using the std::tuple::swap() method. 

    EmpTuple emp1 = std::make_tuple("William", 2, "CEO");
    EmpTuple emp2 = std::make_tuple("Bill", 1, "Chariman");

    std::cout << "Before swap: " << std::endl; 
    std::cout << "emp1:"; printEmp(emp1); 
    std::cout << "emp2:"; printEmp(emp2);

    emp1.swap(emp2);

    std::cout << "After swap: " << std::endl; 
    std::cout << "emp1:"; printEmp(emp1); 
    std::cout << "emp2:"; printEmp(emp2);

    return 0;
}

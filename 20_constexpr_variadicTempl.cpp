#include <iostream>
#include <vector>

/**********

The program shows the usage of,
 
    1. 'constexpr' in C++ 11 
    2. The use of variadic (variable arguments) in templates

    'constexpr' allows evaluating the value of a function at compile time. 
    This allowing the using the function at places where only constants or constant expressions are allowed.

NOTE: Kindly compile with the -DUSECONSTEXPR to prevent the const expression error.
***********/

#if defined(USECONSTEXPR)

constexpr long int sqr(int n)
{ 
    return n*n;
}

#else

long int sqr(int n)
{ 
    return n*n;
}
/***

Error:

g++ 20_constexpr_variadicTempl.cpp -std=c++11

    20_constexpr_variadicTempl.cpp: In function ‘int main(int, char**)’:
    20_constexpr_variadicTempl.cpp:23:33: error: call to non-constexpr function ‘long int sqr(int)’
    enum Val { one=n, square=sqr(n), cube=sqr(n)*n };
    ^
    20_constexpr_variadicTempl.cpp:23:33: error: call to non-constexpr function ‘long int sqr(int)’
    20_constexpr_variadicTempl.cpp:23:35: error: enumerator value for ‘square’ is not an integer constant
    enum Val { one=n, square=sqr(n), cube=sqr(n)*n };
    ^
    20_constexpr_variadicTempl.cpp:23:46: error: call to non-constexpr function ‘long int sqr(int)’
    enum Val { one=n, square=sqr(n), cube=sqr(n)*n };
    ^
    20_constexpr_variadicTempl.cpp:23:46: error: call to non-constexpr function ‘long int sqr(int)’
    20_constexpr_variadicTempl.cpp:23:50: error: enumerator value for ‘cube’ is not an integer constant
    enum Val { one=n, square=sqr(n), cube=sqr(n)*n };
***/
#endif 


/// Variadic Templates

// overloaded method with no arguments passed.
// This is called at the end of recursing each of the arguments passed.
void print() 
{ 
    std::cout << " print() called ... " << std::endl;
} 

template <class T1, typename... T_All>
void print(T1 var1, T_All... var)
{ 
    std::cout << var1 << std::endl ;    // Prints the first argument passed
    print(var...) ;                     // Call the remaining arguments.
} 



int main ( int argc, char *argv[] )
{

/// Constexpr

    const int n=2;
    enum Val { num=n, square=sqr(n), cube=sqr(n)*n };

    std::cout << "constexpr : " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Num: "    << Val::num << std::endl;
    std::cout << "Square: " << Val::square << std::endl;
    std::cout << "Cube: "   << Val::cube << std::endl;

    std::cout << "Variadic Templates: " << std::endl;
    std::cout << "==================================" << std::endl;
    print("The value of ", "PI is", 3.14, "also is ", 22.0/7.0 );

    return 0;
}

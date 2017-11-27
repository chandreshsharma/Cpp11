#include <iostream>

/****

The program demonstrates the usage of the C++ feature of 'User Defined Literals'.

****/


/****

Literals in C++ 98

int i   = 50;       // int literal
float f = 4.5;      // float literal
char c  = 'C';      // character literal
char* s = "Create"; // String literal

***/



/***************************************** String Literal definitions **********************************/

// C++ 11 allows literals to be qualified with user defined names/extensions so that
// the values they represent are more clear logically.


// NOTE:

// The unit translation happens at runtime, and involves runtime cost.
// To save runtime overhead; and considering each of these expressions are literals and can be evaluated at compile time.
// The declarations of the user defined literals can be made constant expressions using 'constexpr' 

// User Defined literals
constexpr long double operator "" _cm(long double x)  { return x * 10; }      // Define _cm as a literal that returns a long double, with value as 10 times x
constexpr long double operator "" _m(long double x)   { return x * 1000; }    // define _m as a literal that returns a long double, with value as 1000 times x
constexpr long double operator "" _mm(long double x)  { return x; }           // define _mm as a base literal that returns a long double.

    #if 0   // Not using a _(underscore) preceding the user defined literal reports the following error.
        8_userdefLiteral.cpp:27:25: warning: literal operator suffixes not preceded by ‘_’ are reserved for future standardization
        long double operator "" cm(long double x)  { return x * 10; } 
    #endif

// Converts a string representation of a binary number into an integer
long int operator "" _bin(const char* str, unsigned int size)
{
	// 	Prior to C++14 (In C++11), the body of a constexpr function must consist solely of a return statement: it cannot have any other statements inside it. 
    //  Hence unlike the User defined literals for height, the constexpr has been removed from here.
	
    long int ret = 0;

    for(int i=0; i<size; ++i)   // On each iteration the number is left shifted by 1
    {
        ret = ret << 1;

        if(str[i] == '1')
            ret += 1;
    }

    return ret;
}

void print(long double h)
{
    std::cout << h << " mm" << std::endl;
}


/***************************************** Main Program **********************************/
int main()
{

// Height
    long double height = 3.4_cm;        //  The _cm indicates that the height is in terms of cms and 
                                        //  would get converted to the default base of millimeters
    print(height); 

    long double h1 = 6.0_m;             // specifies the height in meters.
    print(h1);

    print(3.25_m + 0.3_mm);             // Prints and expression with each of the user defined literals.
    print(1.23_m + 4.5_cm + 0.67_mm);

    print(1300.0_mm / 3.0_m);


// Binary Numbers
    std::cout << "11"_bin << std::endl; 
    std::cout << "10101"_bin << std::endl; 
    std::cout << "1101101"_bin << std::endl; 
    std::cout << "11111"_bin << std::endl; 
    
    return 0;
}

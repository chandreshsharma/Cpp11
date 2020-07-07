#include <iostream>
#include <iomanip>

/****

    The program demonstrates the usage of the C++ feature of 'User Defined Literals'.

    It also shows the explicit initialization of fundamental data types.

****/


/****

Literals in C++ 98

    int i   = 50;       // int literal
    float f = 4.5;      // float literal
    char c  = 'C';      // character literal
    char* s = "Create"; // String literal


User-defined literal is an expression of any of the following forms

    decimal-literal ud-suffix   (1) 
    octal-literal   ud-suffix (2) 
    hex-literal     ud-suffix   (3) 
    binary-literal  ud-suffix    (4) 
    fractional-constant exponent-part(optional) ud-suffix   (5) 
    digit-sequence      exponent-part           ud-suffix  (6) 
    character-literal   ud-suffix (7) 
    string-literal      ud-suffix    (8) 

Examples:

    1-4) user-defined integer literals, such as 12_km
    5-6) user-defined floating-point literals, such as 0.5_Pa
    7) user-defined character literal, such as 'c'_X
    8) user-defined string literal, such as "abd"_L or u"xyz"_M

***/



/***************************************** String Literal definitions **********************************/

// C++ 11 allows user defined names/extensions to be qualified with literals so the values represented are more clear logically.


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

    for(int i=0; i<size; ++i)
    {
        ret = ret << 1;   // On each iteration the number is left shifted by 1

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

////// Explicit Initialization for basic data types

    int i1;
    int i2 = int(); // Initilized to 0
    int i3{};       // Initialized to 0, using initialization list

    std::cout << "int i1: " << i1 << ", i2: " << i2 << ", i3: " << i3 << std::endl;

    float f1, f2=float(), f3{};
    char c1, c2=char(), c3{}; 
    
    std::cout << std::fixed << std::setprecision(3) << "float f1: " << f1 << ", f2: " << f2 << ", f3: " << f3 << std::endl;
    std::cout << "char c1: " << c1 << ", c2: " << c2 << ", c3: " << c3 << std::endl;

    std::cout << std::endl;

// Height
    long double height = 3.4_cm;        //  The _cm indicates that the height is in terms of cms and 
                                        //  would get converted to the default base of millimeters
    std::cout << "3.4_cm: "; print(height); 

    long double h1 = 6.0_m;             // specifies the height in meters.
    std::cout << "6.0_m: "; print(h1);

    std::cout << "(3.25_m + 0.3_mm): "; print(3.25_m + 0.3_mm);             // Prints and expression with each of the user defined literals.
    print(1.23_m + 4.5_cm + 0.67_mm);

    std::cout << "print(1300.0_mm / 3.0_m): "; print(1300.0_mm / 3.0_m);


// Binary Numbers
    std::cout << "11"_bin << std::endl; 
    std::cout << "10101"_bin << std::endl; 
    std::cout << "1101101"_bin << std::endl; 
    std::cout << "11111"_bin << std::endl; 
    
    return 0;
}

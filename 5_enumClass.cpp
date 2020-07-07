#include <iostream>

/****

    The program shows the use of an enum class.
    These are also called scoped enumerations OR strong enumerations.

    The enum class in C++ defines the enum as a normal C++ class.

    The default data type for the enum class variables is 'int'. 
    You can also explicitly define the underlying datatype, say a char.
****/


enum Apple  { Green, Red };
enum Orange { Big, Small, Medium };

enum class ecApple : short int { Green, Red };  // enum class with underlying type 'short int'
enum class ecOrange { Big, Small, Medium };

int main()
{
    enum Apple a = Green;
    enum Orange o = Big;

#if defined(ERROR)
    if (a == o) // Prints "Green Apple is equal to Big Orange", though compilation reports a warning [-Wenum-compare]
        std::cout << "Green Apple is equal to Big Orange" << std::endl;
    else
        std::cout << "Green Apple is not equal to Big Orange !!" << std::endl;
#endif

    ecApple ap = ecApple::Green;
    ecOrange og = ecOrange::Big;
#if defined(ERROR)
    if (ap == og)   ///@@@CS:   Throws a compilation error since ecApple is treated as a C++ class and the == operator
                    //          for the ecApple class that takes a ecOrange object hasn't been defined.
        std::cout << "Green Apple is equal to Big Orange" << std::endl;
    else
        std::cout << "Green Apple is not equal to Big Orange !!" << std::endl;
#endif

/// enum class with datatype 'char'
    enum class Shape : char { Circle, Square, Rectangle, Triangle };

/// enum class with dataype 'char16_t'
    enum class Angle : char16_t { Acute, Right, Obtuse, Straight};

    std::cout << "enum class Shape size(char):           " << sizeof(Shape) << std::endl;
    std::cout << "enum class Angle size(char16_t):       " << sizeof(Angle) << std::endl;
    std::cout << "enum class ecApple size(short int):    " << sizeof(ecApple) << std::endl;
    std::cout << "enum class ecOrange size(default, int):" << sizeof(ecOrange) << std::endl;

    return 0;
}

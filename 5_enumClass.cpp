#include <iostream>

/****

The program shows the use of an enum class

The enum class in C++ defines the enum as a normal C++ class.

****/


enum Apple  { Green, Red };
enum Orange { Big, Small };

enum class App { Green, Red };
enum class Org { Big, Small };

int main()
{
    enum Apple a = Green;
    enum Orange o = Big;

    if (a == o) // Prints "Green Apple is equal to Big Orange", though compilation reports a warning [-Wenum-compare]
        std::cout << "Green Apple is equal to Big Orange" << std::endl;
    else
        std::cout << "Green Apple is not equal to Big Orange !!" << std::endl;

    
    App ap = App::Green;
    Org og = Org::Big;

    if (ap == og)   ///@@@CS:   Throws a compilation error since App is treated as a C++ class and the == operator
                    //          for the App class that takes a Org object hasn't been defined.
        std::cout << "Green Apple is equal to Big Orange" << std::endl;
    else
        std::cout << "Green Apple is not equal to Big Orange !!" << std::endl;

    return 0;
}

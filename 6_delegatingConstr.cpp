#include <iostream>

/*********
The program shows the usage of a delegating contructor in C++ 11.

The delegating constructor allows a constructor to call another constructor without creating another object.

NOTE:
Though any other member initialization needs to appear in the constructor body,
since the delegated constructor would now be respoinsible for creating the object.

********/

class Foo
{
 protected:
    int _n;

 public:
    Foo() { std::cout << "Foo() called with this(" << this << ")" << std::endl; }

    Foo(int n):Foo() 
    { 
        _n = n;
        std::cout << "Foo(int) called with this(" << this << ")" << std::endl; 
    }
};

#define DEBUG 1

int main()
{
    /// Static assertion would fail for a non 32 bit machine

    static_assert((DEBUG == 1), "Debug not enabled ...");

    static_assert((sizeof(int) == 8), "Code works only for Machines where int size is 8");


    Foo foo1;
    Foo foo2(10);

    return 0;
}


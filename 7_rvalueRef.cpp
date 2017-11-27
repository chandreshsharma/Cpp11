#include <iostream>
#include <algorithm>

/****

The program demonstrates the usage of the C++ feature of 'rvalue reference'.

****/


/******** Overloaded functions based of parameter types ********/

// The below two functions are examples of function overloading by reference type

// Each of the functions accept an integer, however a && indicates an rvalue reference.
// The fuction called with an rvalue would invoke this version.

void intRef(int& i) { std::cout << "lvalue reference version called ... " << i << std::endl; }      // Function with lvalue reference as parameter
void intRef(int&& i) { std::cout << "rvalue reference version called ... " << i << std::endl; }     // Function with rvalue reference as parameter

#if 0
void intRef(int i) { }  // Would report an error, since the compiler wouldn't know whether to call the (int i) OR (int &i)

error: call of overloaded ‘intRef(int&)’ is ambiguous
#endif


/******** Vector class using the rvalue reference for move semantics **********/

template <class T>
class Vec
{
public:
    int _size;
    T* _arr;

    Vec(unsigned int size = 1)   // default constructor
    {
        std::cout << "(Vec) default constructor called for: " << this << std::endl;
        _size = size;
        _arr = new T[_size];
    }

    Vec(const Vec & vec)   // Copy Constructor, called when the parameter is a lvalue.
    {
        std::cout << "(Vec) Copy Constructor called ..." << std::endl;
        _size = vec._size;
        _arr = new T[_size];

        for(unsigned i = 0; i < _size; ++i) // Deep Copy the contents to the new vector
            _arr[i] = vec._arr[i];
    }

    Vec(Vec&& rhs)   // Move Constructor, called when the parameter is a rvalue.
    {   
        std::cout << "(Vec) Move Constructor called for:" << this << ", rhs:" <<&rhs << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;

        rhs._arr = nullptr;
    }
	
	Vec & operator = (Vec && rhs) // Copy Assignment operator with move semantics
    {
        std::cout << "Assignment Operator(Move Semantics) called ..." << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;

        rhs._arr = nullptr;
    }

    Vec & operator = (Vec const & rhs) // Assignment operator with copy semantics
    {
        std::cout << "Assignment Operator(Copy Semantics) called ..." << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;
    }
};

class MyIntVec
{
public:
    int _size;
    int* _arr;

    MyIntVec(unsigned int size = 1)   // default constructor
    {
        std::cout << "(MyIntVec) default constructor called ..." << std::endl;
        _size = size;
        _arr = new int[_size];
    }

    MyIntVec(const MyIntVec & vec)   // Copy Constructor, called when the parameter is a lvalue.
    {
        std::cout << "(MyIntVec) Copy Constructor called ..." << std::endl;
        _size = vec._size;
        _arr = new int[_size];

        for(unsigned i = 0; i < _size; ++i) // Deep Copy the contents to the new vector
            _arr[i] = vec._arr[i];
    }

    MyIntVec(MyIntVec && rhs)   // Move Constructor, called when the parameter is a rvalue.
    {   
        std::cout << "(MyIntVec) Move Constructor called ..." << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;

        rhs._arr = nullptr;
    }

    MyIntVec & operator = (MyIntVec && rhs) // Copy Assignment operator with move semantics
    {
        std::cout << "Assignment Operator(Move Semantics) called ..." << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;

        rhs._arr = nullptr;
    }

    MyIntVec & operator = (MyIntVec const & rhs) // Assignment operator with copy semantics
    {
        std::cout << "Assignment Operator(Copy Semantics) called ..." << std::endl;
        _size = rhs._size;
        _arr = rhs._arr;
    }
};

template <class T>
void foo(Vec<T> vec)
{
    std::cout << "Inside foo : _arr:" << vec._arr << std::endl;
}

void foo(MyIntVec vec)
{
    std::cout << "Inside foo : _arr:" << vec._arr << std::endl;
}

MyIntVec getIntVec() 
{ 
    return MyIntVec();  // This is the temporary value returned.
}

/********* Main *********/

int main()
{

#if 0
    int a  = 10;    // a is an lvalue
    int& b = a;     // b is an lvalue reference (reference)

//  int&& c;     // c is an rvalue reference.

    intRef(a);      // a is an lvalue
    intRef(b);      // b is an lvalue, alias for a

    intRef(30);     // 30 is a constant and an rvalue.

#endif

/*****
std::move:

    std::move() is a helper function to force move semantics on values, even if they have a name.
    Directly using the returned value causes arg to be considered an rvalue.

*****/

/////// Vec class
    std::cout<< "=================== Vec ======================" << std::endl;
    Vec<int> vec(5);                    // Calls the default constructor

    Vec<int> newVec(std::move(vec));    // vec._arr would now be nullptr

    std::cout << "vec._arr after std::move(vec):" << vec._arr << std::endl;

    foo(newVec);                        // Calls the Copy Constructor

    foo(Vec<float>(5));                 // Even though this creates a temporary object that is passed to foo, its treated as an lvalue.

/////// MyIntVec

    std::cout<< "=================== MyIntVec ======================" << std::endl;
    foo( std::move(getIntVec()) );

    MyIntVec myVec, myVec1, myVec2;

    myVec1 = std::move(myVec);          // Calls the Assignment operator with Move semantics
    
    myVec2 = myVec;                     // Calls the Assignment operator with Copy Semantics

//    MyIntVec myVec2; myVec2 = MyIntVec();

    return 0;
}

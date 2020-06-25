#include <iostream>
#include <vector>
#include <list>

/********
The program shows and example of Uniform Initialization.

The Aggregate Initializor allow an object to be initialized using Aggregate Initializer,
like initializing an array in C++03.

C++ 11 extends the scope of Aggregate Initialization by 
allowing an object to be initialized by passing multiple arguments in braces,
if there exists a constructor for the class that would create the object of the class using these arguments.

C++ 11 also defines a template class 'template <class T> std::initializer_list' to access a list of objects of type 'const T'.
*******/

class Car
{
protected:

	std::string company;
	std::string model;
	int gears;

public:
	Car(std::string c, std::string m, int g): company(c), model(m), gears(g)    {
	}

	void print()    {
		std::cout << "Co: " << company << ", Model: " << model << ", Number of Gears:" << gears << std::endl;
	}
};

void printInt(int a, int b) {
    std::cout << "printInt(int a, int b) called ..." << std::endl;
    std::cout << a << ", " << b << std::endl;
}

void printInt(std::initializer_list<int> initList ) {
    std::cout << "printInt(std::initializer_list<int>) called ..." << std::endl;

    for(auto it = initList.begin(); it != initList.end(); ++it)
        std::cout << *it << ", ";

    std::cout << std::endl;
}


int main()
{
    /*************** User Defined types *****************/
	Car c1 = {"Maruti", "WagonR", 5};
	Car c2 {"Honda", "Civic", 5};       // The assignment operator is optional

	/***** Error reported in case of C++ 03
		2_uniformInit.cpp:38:30: error: in C++98 ‘c2’ must be initialized by constructor, not by ‘{...}’
  		Car c2 = {"Honda", "Civc", 5};
	******/

    /**************** STL Containers ******************/
    std::vector<int> nVec {1, 2, 3, 4, 5 };
    std::list<std::string> strList { "This", "is", "a", "list", "of", "strings" };

	c1.print();
	c2.print();

    for(auto i:nVec) 
        std::cout << i << ", "; std::cout << std::endl;

    for(auto s:strList) 
        std::cout << s << " "; std::cout << std::endl;

    /**************** Basic Data Types **************/

    int i {};       // Initialized to 0
    int i1;         // Value Undefined

    double d {};    // Initialized to 0.0
    double d1;      // Value Undefined

    int * nPtr {};  // Initialized to nullptr
    int * nPtr1;    // Pointer Undefined.

    std::cout << "i: " << i << ", i1: " << i1 << std::endl;
    std::cout << "d: " << i << ", d1: " << d1 << std::endl;
    std::cout << "nPtr: " << nPtr << ", nPtr1: " << nPtr1 << std::endl;

    
    /**************** std::initializer_list **************/

    printInt(10, 20);

    printInt({10, 20});             // Explicit Conversion
    printInt({10, 20, 30, 40, 50}); // Explicit Conversion

    std::initializer_list<int> il = {100, 200 };
    printInt(il);

	return 0;
}

#include <iostream>

/********

The program shows and example of Uniform Initialization.

The Aggregate Initializor allow an object to be initialized using Aggregate Initializer,
like initializing an array in C++03.

C++ 11 extends the scope of Aggregate Initialization by 
allowing an object to be initialized by passing multiple arguments in braces,
if there exists a constructor for the class that would create the object of the class using these arguments.

*******/

class Car
{
protected:

	std::string company;
	std::string model;
	int gears;

public:
	Car(std::string c, std::string m, int g): company(c), model(m), gears(g)
	{
	}

	void print()
	{
		std::cout << "Co: " << company << ", Model: " << model << ", Number of Gears:" << gears << std::endl;
	}
};

int main()
{
	Car c1 = {"Maruti", "WagonR", 5};
	Car c2 = {"Honda", "Civc", 5};

	/***** Error reported in case of C++ 03

		2_uniformInit.cpp:38:30: error: in C++98 ‘c2’ must be initialized by constructor, not by ‘{...}’
  		Car c2 = {"Honda", "Civc", 5};

	******/

	c1.print();
	c2.print();

	return 0;
}

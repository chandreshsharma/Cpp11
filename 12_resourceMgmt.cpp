#include <iostream>
#include <vector>

/********
    The program to show resource management when a class contains a pointer to an object of another class.
*********/

class Car
{
public:
    Car(std::string model): _modelName(new std::string(model)) { }

    ~Car() { delete _modelName; _modelName = nullptr; }


    // C++ 11 allows to delete a default declaration of a method.
    // So in the current case we delete the default constructor and the default Assignment operator.
#if defined DELETECC
    Car(const Car& rhs) = delete;
    Car& operator = (const Car& rhs) = delete;
#endif

    void printName() { std::cout << "_model: " << *_modelName << std::endl; }

protected:
    std::string * _modelName;

#if 0
    Car(const Car& rhs);                // Declaring the Copy Constructor and Assignment operator as protected,
    Car& operator = (const Car& rhs);   // prevents any implicit invocation of the methods.
#endif

};

int main()
{
    std::vector <Car> cars;

/**

C++ pre-C++98: 	__cplusplus is 1.
C++98: 			__cplusplus is 199711L.
C++11: 			__cplusplus is 201103L.
C++14: 			__cplusplus is 201402L.
C++17: 			__cplusplus is 201703L.

**/	
	
#if __cplusplus >= 201103L      // Check if this is a version that supports emplace_back, i.e. C++ 11 or further

    cars.emplace_back("Maruti");    // emplace_back() appends the element to the end of the list.
                                    // The element is constructed in place with the arguments passed used as arguments for the object's constructor.
#else

    cars.push_back(Car("Maruti"));  // Create a car object and push to the container.

                                    // The program causes a potential crash at this point since the Car("Maruti) was created as a temporary object
                                    // and copied to the object pushed in cars using the default Copy Constructor.
            
                                    // The default Copy Constructor does a shallow copy, so rather than allocating a new pointer address for _modelName
                                    // it copies address, as in the temporary object.
                                    // The temporary object is destroyed after the push_back call completes, however the same address is held inside '_modelName'.
                                    // dereferencing this in printName causes a crash.

                                    // The solution to this is
                                    // 1. Overload the default Copy Constructor and the Assignment Operator with Deep Copy Semantics.
                                    // 2. Delete the Copy Constructor and the Assignment operator by declaring them as protected/private.
#endif

    cars.front().printName();       // Prints the first object in the cars container
                                    
    return 0;
}

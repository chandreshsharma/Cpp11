#include <iostream>
#include <memory>   // To include weak_ptr
#include <stdexcept>

/*****
A program to show the usage of a unique_ptr.

A unique pointer defined by std::unique_ptr<T>, represents an exclusive ownership of an object.

Unlike shared_ptr where multiple objects can share ownership of the same object,
for a unique_ptr, the ownership can be owned by only one unique pointer.
The object is automatically deleted, when the unique_ptr goes out of scope or is assigned to something else.

A unique_ptr is lightweight compared to a shared_ptr, so for an object which is not shared,
its better to use a unique_ptr than a shared_ptr.

A unique_ptr is the closest alternative to using a raw pointer, with the advantage of 
not having to worry about the memory leak in case of an exception, forgetting to release memory, etc.


Methods:
========

unique_ptr::reset(ptr = pointer())  Release the currently managed object, and starts managing the new object pointed by ptr.
unique_ptr::release()               Releases the currently managed object, returning the raw pointer to the object.

unique_ptr ptr = std::move(unique_ptr p1)   Assign a unique_ptr to a new object using std::move(Rvalue reference); this deletes
                                            the old unique_ptr object, and the object is now managed by the new unique_ptr. 

unique_ptr ptr = nullptr;           Deletes the unique_ptr object.
                                    Also deletes the managed object, calling the destructor for cleanup.
*****/


class Shape
{
public:
    Shape(int i=0):_i(i) 	{ std::cout << "Shape constructor <" << this << "> i:" << _i << std::endl; }
	
    Shape(const Shape& foo):_i(foo._i) { std::cout << "Shape copy constructor <" << this << ">" << std::endl; }

    ~Shape() { std::cout << "Shape destructor <" << this << ">" << std::endl; }

    void draw() 
	{ 
	    std::cout << "Drawing <" << this << "> with _i:" << _i << std::endl;
	}
	
protected:
    int _i;
};

class Colour
{
public:
    Colour() { std::cout << "Colour constructor ..." << std::endl; } 
    ~Colour() { std::cout << "Colour destructor ..." << std::endl; } 
};

class Square
{
public:
    Square(int l):_len(l), _col(new Colour())
    {
    
        try
        {
 
            if(_len < 0)
            {
                throw std::invalid_argument("Length cant be less than 0");
            }
        }
        catch(std::invalid_argument & ia)
        {
            std::cout << "Caught an invalid_argument exception :" << ia.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "Caught an exception ..." << std::endl;
        }
    }    
protected:
    double _len;

#if !defined(UNIQUE_PTR)    // NOTE: When a std::unique_ptr is used instead of a raw pointer the desctructor is called
    Colour* _col;           // freeing the allocated memory.
#else                       // In case of a raw pointer the memory is leaked.
    std::unique_ptr<Colour> _col;
#endif

};

void print(const std::unique_ptr<Shape> & uptr)
{
    std::cout << "get(): " << uptr.get() << std::endl;

    if(uptr.get() != nullptr)
        uptr->draw();
}

int main()
{
    std::cout << "----------------------- uptr1 -----------------------" << std::endl;
    std::unique_ptr<Shape> uptr1(new Shape(12345));
    print(uptr1);

    std::cout << "----------------------- uptr2 -----------------------" << std::endl;
    std::unique_ptr<Shape> uptr2(new Shape(1122));
    print(uptr2);
    std::cout << "After reassignment " << std::endl; 
    uptr2 = std::move(uptr1);   // Assign uptr1 to uptr2 using move semantics;
                                // The original object (Shape(1122)) managed by unique_ptr object uptr2 is deleted.
                                // The uptr1 unique pointer object becomes empty.
                                // The unique_ptr object uptr2 now manages Shape(12345).
    std::cout << "uptr1:" << std::endl;
    print(uptr1);
    std::cout << "uptr2:" << std::endl;
    print(uptr2);

    std::cout << "----------------------- uptr3 -----------------------" << std::endl;
    std::unique_ptr<Shape> uptr3(new Shape(99));
    print(uptr3);

    uptr3.reset(new Shape(123));    // Reset releases the managed object(Shape(99)) and starts managing Shape(123).
    std::cout << "----------------------- uptr3, after reset -----------------------" << std::endl;
    print(uptr3);

    std::cout << "----------------------- uptr3, after release -----------------------" << std::endl;
    Shape *ptr = uptr3.release();   // release() returns a pointer to the object and releases ownership
                                    // uptr3 is no longer managing the object. The memory would need to be freed explicitly.
    print(uptr3);

    delete ptr; ptr = nullptr;      // Call the delete explicitly

    std::cout << "----------------------- uptr4 -----------------------" << std::endl;
    std::unique_ptr<Shape> uptr4(new Shape(100));
    print(uptr4);

    std::cout << "----------------------- uptr2, uptr4, being assigned to nullptr -----------------------" << std::endl;
    uptr2 = nullptr;    
    uptr4 = nullptr;    // Assigning a unique pointer to nullptr deletes the unique_ptr object.
                        // It also calls the destructor of the object being managed.
    std::cout << "uptr2: " << std::endl;
    print(uptr2);
    std::cout << "uptr4: " << std::endl;
    print(uptr4);


    // Create an array of unique_ptr
    std::unique_ptr<Shape[]> uptrs(new Shape[4]);

    // delete[] uptrs;      Throws a compilation error.
                                                        // The objects are eventually deleted when the program ends.
                                                        // Not aware if an explicit operator exists to delete the array of pointers.

    // Example to show the use of unique_ptr vs raw pointers.

    Square s(-1);


    std::cout << "Returning from main() ..." << std::endl;

    return 0;
}

#include <iostream>
#include <memory>   // To include weak_ptr

/*****
A program to show the usage of a weak_ptr.

std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::weak_ptr. 
It must be converted to std::weak_ptr in order to access the referenced object.

A weak pointer wants access to an object, without having an ownership of the object.
So weak_ptr doesnt track when and how the object would be deleted.

Methods:
========

weak_ptr::use_count() 	returns the reference count for the weak_ptr objects pointing to the object.
weak_ptr::expired()   	Returns whether the weak_ptr object is either empty OR 
						there are no more shared_ptr in the owner group it belongs to.
weak_ptr::lock()    	Returns a shared_ptr with the information preserved by the weak_ptr object if it is not expired.

Use weak_ptr works as a temporary ownership, to allow access to an object only if it exists.

weak_ptr is converted to shared_ptr to get a temporary ownership of the object.
If the original shared_ptr object goes out of scope or is destroyed, the object's lifetime is extended till the shared_ptr persists.

*****/

class Shape
{
public:
    Shape() 			{ std::cout << "Shape constructor <" << this << ">" << std::endl; }
    Shape(int i):_i(i) 	{ std::cout << "Shape constructor <" << this << "> i:" << _i << std::endl; }
	
    Shape(const Shape& foo):_i(foo._i) { std::cout << "Shape copy constructor <" << this << ">" << std::endl; }

    ~Shape() { std::cout << "Shape destructor <" << this << ">" << std::endl; }

    void draw() 
	{ 
	    std::cout << "<" << this << "> _i:" << _i << std::endl;
	}
	
protected:
    int _i;
//	std::weak_ptr<Shape> _wptr;		// defining the _ptr as a weak_ptr creates an interface to access the object.
									// However weak_ptr doesn't manage the lifetime of the object.
};

void printWP(std::weak_ptr<Shape> wp)
{
    if(wp.expired()) 
        std::cout << "weak_ptr<Shape> expired !!" << std::endl; 
    else
        wp.lock()->draw();
}

int main()
{
    std::shared_ptr<Shape> sp = std::make_shared<Shape>(1212);
	std::weak_ptr<Shape> wp = sp;

    printWP(wp);

    sp.reset();

    printWP(wp);

    return 0;
}

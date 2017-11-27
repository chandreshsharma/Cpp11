#include <iostream>
#include <memory>   // To include shared_ptr

/*****
A program to show the usage of a shared_ptr.

shared_ptr uses reference count semantics, so the pointer is desctructed when the count becomes 0.

Methods:
========

shared_ptr::use_count() returns the reference count for the pointer.
shared_ptr::get()       returns the raw pointer to the enclosed object.
shared_ptr::unique()    returns if the pointer is being shared, i.e. has more than a single object associated.

shared_ptr::operator -> is overloaded to point to the object(raw pointer) referred by the shared_ptr.
shared_ptr::operator * (dereference) is overloaded to point to the object(raw pointer), referred by the shared_ptr.

NOTE: Avoid using the raw pointer once you have created a shared_ptr for the same.

// A raw pointer can be cast to another pointer. shared_ptr provides the same drawtionality using,
// static_pointer_cast
// dynamic_pointer_cast
// const_pointer_cast
*****/

class Shape
{
public:
    Shape() { std::cout << "Shape constructor <" << this << ">" << std::endl; }
    Shape(int i):_i(i) { std::cout << "Shape constructor <" << this << "> i:" << _i << std::endl; }
    Shape(const Shape& foo):_i(foo._i) { std::cout << "Shape copy constructor <" << this << ">" << std::endl; }

    ~Shape() { std::cout << "Shape destructor <" << this << ">" << std::endl; }

    void draw() { std::cout << "Inside foo::draw(), _i:" << _i << std::endl; }
protected:
    int _i;
};

void print(const std::shared_ptr<Shape> & sp)
{
    std::cout << "use_count:" << sp.use_count() << ", get(): " << sp.get() 
              << ", unique(): " << std::boolalpha << sp.unique() << std::endl;

    sp->draw(); // The shared_ptr is dereferenced to call the object's method.
}

int main()
{
    std::shared_ptr<Shape> sp1(new Shape(123));
    std::cout << "----------------- sp1 ----------------" << std::endl;
    print(sp1);

    std::shared_ptr<Shape> sp2 = sp1;
    std::cout << "----------------- sp2 ----------------" << std::endl;
    print(sp2);

// C++ provides a way of combining the steps to create a object and create a shared ptr of the object.

    std::shared_ptr<Shape> sp3 = std::make_shared<Shape>(1000);
    std::cout << "----------------- sp3 ----------------" << std::endl;
    print(sp3);

    // The dereference operator can also be used.
    std::cout << "Calling draw() using the dereference operator" << std::endl;
    (*sp3).draw();

// Assigning a shared_ptr to another transfers the ownership to the assignor, the original assignor gets deleted
// AND points to the assignee.
// The assignee continues to point to the same object, with the use_count incremented

    std::shared_ptr<Shape> sp4 = std::make_shared<Shape>(50);
    std::cout << "----------------- sp4 ----------------" << std::endl;
    print(sp4);

    sp3 = sp4;      // sp3 gets deleted AND sp3 now points to sp4
    std::cout << "After sp3 = sp4, sp3.get(): " << sp3.get() <<  ",sp3.use_count():" << sp3.use_count() 
              << ", sp4.get(): " << sp4.get() << ", sp4.use_count(): " << sp4.use_count()  << std::endl;

    sp3 = nullptr;  // sp1 gets deleted AND points to nullptr
    std::cout << "After sp3 = nullptr, sp3.get(): " << sp3.get() <<  ",sp3.use_count():" << sp3.use_count() 
              << ", sp4.get(): " << sp4.get() << ", sp4.use_count(): " << sp4.use_count()  << std::endl;

// Calling reset() deletes the pointer.
    sp4.reset();
    std::cout << "After sp4.reset(), sp4.get(): " << sp4.get() <<  ",sp4.use_count():" << sp4.use_count() << std::endl;
    

// Custom deletor
// C++ 11 allows you to define your own deleter function(called when the objected is deleted),
// rather than the default 'operator delete'
//
// Here though you need to use the share_ptr constructor

// Custom delete funtion defined using lambda function
    std::shared_ptr<Shape> sp = std::shared_ptr<Shape>(new Shape(1122),
                                [](Shape * s) { std::cout << "Using custom delete..." << std::endl; delete s; s = nullptr; });

// One of the cases where a custom deletor would be needed is when the shared_ptr is used to allocate,
// an array of objects on the heap.

    std::cout << "---------------- Allocating an array of pointers using shared_ptr --------------------" << std::endl;
    std::shared_ptr<Shape> spArr = std::shared_ptr<Shape>(new Shape[3], [](Shape * s) { delete[] s; s = nullptr; });

// In case the custom deletor had not been defined a normal delete would have been called resulting in freeing up
// only the first element spArr[0] and leaking the rest of the array elements



#if 0   // 1. An object should be assigned to a shared_ptr as soon as it is created.
        // 2. An object should be assigned to a shared_ptr only once.

        // In the example below the same object is assigned to two smart pointers.
        // This is an incorrect way of using shared_ptr since the object is destroyed
        // when the first shared_ptr goes out of scope and the reference count goes to 0.

        // When the second shared_ptr goes out of scope the original object is already destroyed
        // and the result is undefined.

    Shape* fooPtr = new Shape(12345);
    shared_ptr<Shape> sp1(fooPtr); // use_count() = 1
    shared_ptr<Shape> sp2(fooPtr); // use_count() = 1, Behaviour undefined when sp2 goes out of scope

#endif

    return 0;
}

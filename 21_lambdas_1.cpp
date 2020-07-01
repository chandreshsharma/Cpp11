#include <iostream>
#include <typeinfo>


/*****

    The program shows the concept of lambda functions OR lambda expressions.

    A lambda works similar to an overloaded () method (functor) or a macro.

    A lambda has the format of,
    [ captures ] ( params ) mutable(opt) -> ret(opt) { body }
    
    captures:   defines the list of comma separated variables(known as captures) defined outside the lambda, 
                that need to be accessed from within the lambda function body.

                By default the variables of the outer scope that define the lambda are not accessible within the lambda.
                To allow access you need to capture the variable in the 'capture list' OR 'captures'.
    
                The default capture can be defined of type reference or value(a copy)
                [&] (capture the outer scope variables by reference) and
                [=] (capture the outer scope variables by value or access a copy).

    params:     list of parameters passed to the lambda, like arguments passed to a function/method.

    ret:        return type of the lambda.
                This is optional and for a simple lambda, the return type can be deduced from the 'return <val>' statement.

    body:       The lambda function body



    References:  
    https://en.cppreference.com/w/cpp/language/lambda 

******/

int main() {

    std::cout << "\n/****************** Simple Lambda function *********************/ " << std::endl;
    auto simple = [] { std::cout << "A simple lambda function ..." << std::endl; };
    simple();

    int i = 10, j = 20, k = 30;

    auto val = [i] { std::cout << "Pass capture by value i:" << i << std::endl; /** i++; **/ };
    val();

    auto ref = [&j] { j+= 5; std::cout << "Pass caputure by reference j:" << j << std::endl; }; 
    ref();

///////// Access variables by reference //////////

    std::cout << "\n/****************** capture accessed by reference *********************/ " << std::endl;
    // [&] definition specifies all variables accessed by reference inside the lambda
    auto refLambda = [&]() { 
        i = i*1;
        j = j*2;
        k = k*3;

        std::cout << "values in refLambda(), i: " << i << ", j: " << j << ", k:" << k << std::endl;
    };

    refLambda();
    std::cout << "values updated in refLambda(), i: " << i << ", j: " << j << ", k:" << k << std::endl;


//////// Access a copy of the variables //////////

    std::cout << "\n/****************** capture accessed by value *********************/ " << std::endl;
    // [=] definition specifies all varaiables accessed by value OR creating a copy inside the lambda
    auto copyLambda = [=]() { 

    // Since the values are accessed by copy the original variables are Read Only.
    // The compiler throws an error as below.

#if 0    
        i = i*1;
        j = j*2;
        k = k*3;

Error:
        21_lambdas.cpp:57:11: error: assignment of read-only variable ‘i’
                i = i*1;
                  ^
        21_lambdas.cpp:58:11: error: assignment of read-only variable ‘j’
                j = j*2;
                  ^
        21_lambdas.cpp:59:11: error: assignment of read-only variable ‘k’
                k = k*3;
                  ^
#endif
    };
    copyLambda();

///////// Access variables by reference, except the variable k //////////

    std::cout << "\n/****************** capture accessed by reference, except k *********************/ " << std::endl;
    auto refL = [&, k]()   {
        i += 10;
        j += 20;
    
    // The variable k is defined to be accessed as a copy, hence would throw a Read Only error.
#if 0
        k += 30;

Error:
        21_lambdas.cpp: In lambda function:
        21_lambdas.cpp:85:11: error: assignment of read-only variable ‘k’
                k += 30;
                  ^
#endif
    };

    refL();
    std::cout << "Updated values, i:" << i <<", j: " << j << ", k: " << k << std::endl;
    
///////// Access variables by value, except the variables j and k //////////

    std::cout << "\n/****************** capture accessed by value, except j and k *********************/ " << std::endl;
    auto copyL = [=, &j, &k]()   {
    
    //  The default capture type is copy. The &j and &k declaration overrides this to capture by reference. 
    //  updating i throws an error when the value is attempted to be updated.
#if 0
        i += 10;

Error:
        21_lambdas.cpp: In lambda function:
        21_lambdas.cpp:109:11: error: assignment of read-only variable ‘i’
                i += 10;
                  ^
#endif
        j += 20;
        k += 30;
    };

    copyL();
    std::cout << "Updated values, i:" << i <<", j: " << j << ", k: " << k << std::endl;

///////// Access variables by value, allow values to be updated within the lambda //////////

// To allow captures passed to be writeable within the lambda use the keyword 'mutable'
    std::cout << "\n/****************** mutable lambda, capture accessed by value*********************/ " << std::endl;
    auto mutableLambda = [=] () mutable { 

        i = i*1;
        j = j*2;
        k = k*3;

        std::cout << "Inside mutableLambda, i:" << i <<", j: " << j << ", k: " << k << std::endl;
    };

    mutableLambda();
    std::cout << "Post mutableLambda() call, values i:" << i <<", j: " << j << ", k: " << k << std::endl;


////////// Lambda with explicit return type //////////  

    std::cout << "\n/****************** explicit return type defined *********************/ " << std::endl;
    auto PI1 = []()->double { return 22.0/7.0; };
    std::cout << typeid(PI1()).name() << std::endl;  

////////// Lambda with return type deduced on value returned //////////  
    std::cout << " /****************** implicit return type *********************/ " << std::endl;
    auto PI2 = []() { return 22.0/7.0; };
    std::cout << typeid(PI2()).name() << std::endl; 

    return 0;
}

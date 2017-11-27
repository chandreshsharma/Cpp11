#include <iostream>

/*****
 A program to show the C++ 11 'nullptr' keyboard.

*****/


void foo(int) { std::cout << "Inside foo_int ..." << std::endl; }

void foo(char *) { std::cout << "Inside foo_charPtr..." << std::endl; }


int main()
{
    foo(NULL);  // Calls the foo(int) in C++ 03, whereas the intention might have been to call foo(char *),
                // since C++ treats NULL as 0.

                // Besides also reports the warning with -Wconversion-null

    foo(nullptr);

    return 0;
}

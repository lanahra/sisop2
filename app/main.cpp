#include <stdlib.h>
#include <iostream>

#include "example.h"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
    // Bring in the dummy class from the example source,
    // just to show that it is accessible from main.cpp.
    Dummy d = Dummy();
    return d.doSomething() ? 0 : -1;
}

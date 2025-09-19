// g++ -shared -fPIC -o liblib.so lib.cpp
#include <iostream>


void lfunc() {
    std::cout << "Hello from cpp shared lib" << std::endl;
}
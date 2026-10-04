#include <iostream>

#include "Tests/Tests.h"

int main() {
    std::cout << "Hello BoronMathLib" << std::endl;
    
    Tests::doTests();

    return 0;
}

//Times
/*
Vec2:
	Average: 16.10 ns
*/
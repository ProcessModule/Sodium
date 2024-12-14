// entrypoint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "initalizer.hpp"

int main()
{
    std::cout << "Starting driver initialization.." << std::endl;

    initialize();

    return 0;
}
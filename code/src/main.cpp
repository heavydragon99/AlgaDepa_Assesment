#include <iostream>

#include "controller.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    controller controller;
    controller.createLevel();

    return 0;
}
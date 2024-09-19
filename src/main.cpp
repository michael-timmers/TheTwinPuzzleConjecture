#include <iostream>

#include "puzzle.hpp"

int main() {
    std::cout << "The Twin Puzzle Conjecture\n";

    Puzzle puzzle(3, 3, 2);
    puzzle.display();

    return 0;
}
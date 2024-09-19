#include <iostream>

#include "puzzle.hpp"
#include "puzzlesolver.hpp"

int main() {
    std::cout << "The Twin Puzzle Conjecture\n";

    Puzzle puzzle(2, 2, 2);
    puzzle.display();

    PuzzleSolver solver(puzzle);
    solver.findNewPuzzles();
    solver.displaySolvedPuzzles();

    return 0;
}
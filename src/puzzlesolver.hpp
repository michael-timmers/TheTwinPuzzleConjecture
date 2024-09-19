#pragma once

#include "puzzle.hpp"

class PuzzleSolver {
   public:
    Puzzle board;
    std::vector<Puzzle> solvedPuzzles;

    PuzzleSolver(Puzzle board);

    void findNewPuzzles();

   private:
    void tryPlacingPieces();
    bool tryPlacingPiece();
};
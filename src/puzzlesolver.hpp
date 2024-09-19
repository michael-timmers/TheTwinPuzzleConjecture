#pragma once

#include "puzzle.hpp"

class PuzzleSolver {
   public:
    Puzzle initBoard;
    std::vector<Piece> allPieces;
    std::vector<Puzzle> solvedPuzzles;

    PuzzleSolver(Puzzle filledPuzzle);

    void findNewPuzzles();

   private:
    void tryPlacingPieces(Puzzle board, std::vector<Piece> unplaced);
    bool tryPlacingPiece(Puzzle board, size_t row, size_t col, Piece piece);
};
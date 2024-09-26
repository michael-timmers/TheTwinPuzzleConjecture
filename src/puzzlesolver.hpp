#pragma once

#include <vector>
#include <ranges>

#include "puzzle.hpp"

class PuzzleSolver {
   public:
    Puzzle initBoard;
    std::vector<Piece> allPieces;
    std::vector<Puzzle> solvedPuzzles;

    PuzzleSolver(Puzzle filledPuzzle);

    void findNewPuzzles();

    void displaySolvedPuzzles();

   private:
    void placePieces(Puzzle board, std::ranges::input_range auto unplaced);
    bool tryPlacingPiece(Puzzle& board, size_t row, size_t col, Piece piece);

    void displayPieceList(std::ranges::input_range auto pieces);
};
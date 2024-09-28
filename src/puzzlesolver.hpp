#pragma once

#include <vector>

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
    void placePieces(Puzzle board, const std::vector<Piece>& unplaced);
    bool tryPlacingPiece(Puzzle& board, size_t row, size_t col, Piece piece);

    void displayPieceList(const std::vector<Piece>& pieces);
    void removeDuplicatedPuzzles();
};
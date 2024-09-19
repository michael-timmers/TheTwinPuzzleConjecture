#include <iostream>

#include "puzzlesolver.hpp"

PuzzleSolver::PuzzleSolver(Puzzle filledPuzzle)
    : initBoard(filledPuzzle.cols, filledPuzzle.rows, filledPuzzle.duplicationsAllowed),
      allPieces(filledPuzzle.pieces) {
}

void PuzzleSolver::findNewPuzzles() {
    tryPlacingPieces(initBoard, allPieces);
}

void PuzzleSolver::displaySolvedPuzzles() {
    std::cout << solvedPuzzles.size() << " Solved puzles:\n";
    for (auto puzzle : solvedPuzzles) {
        std::cout << "puzzle:\n";
        puzzle.display();
    }
}

void PuzzleSolver::tryPlacingPieces(Puzzle board, std::vector<Piece> unplaced) {
    for (size_t i = 0; i < board.rows; i++) {
        for (size_t j = 0; j < board.cols; j++) {
            for (int k = 0; k < unplaced.size(); k++) {
                if (tryPlacingPiece(board, i, j, unplaced[k])) {
                    unplaced.erase(unplaced.begin() + k);
                    tryPlacingPieces(board, unplaced);
                }
            }
        }
    }
    solvedPuzzles.push_back(board);
}

bool PuzzleSolver::tryPlacingPiece(Puzzle board, size_t row, size_t col, Piece piece) {
    if (!board(row, col).isPlaced) {
        for (int i = 0; i < 4; i++) {
            if (board.fits(piece, row, col)) {
                board.place(piece, row, col);
                return true;
            }
        }
    }
    return false;
}
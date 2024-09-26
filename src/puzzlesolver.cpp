#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>

#include "puzzlesolver.hpp"

PuzzleSolver::PuzzleSolver(Puzzle filledPuzzle)
    : initBoard(filledPuzzle.cols, filledPuzzle.rows, filledPuzzle.duplicationsAllowed, false),
      allPieces(filledPuzzle.pieces) {
}

void PuzzleSolver::findNewPuzzles() {
    std::cout << "Finding sollutions with " << allPieces.size() << "pieces and " << initBoard.cols << " by " << initBoard.rows << " board\n";
    auto unplacedPieces = std::views::all(allPieces);

    placePieces(initBoard, unplacedPieces);
}

void PuzzleSolver::displaySolvedPuzzles() {
    std::cout << solvedPuzzles.size() << " Solved puzles:\n";
    for (auto puzzle : solvedPuzzles) {
        std::cout << "puzzle:\n";
        puzzle.display();
    }
}

void PuzzleSolver::placePieces(Puzzle board, std::ranges::input_range auto unplaced) {
    // std::cout << "New branch with " << std::ranges::distance(unplaced) << " pieces:\n";
    displayPieceList(unplaced);
    int splitCount = 0, k = 0;
    for (Piece p : unplaced) {
        std::cout << "checking " << k << "th piece\n";
        for (size_t i = 0; i < board.rows; i++) {
            for (size_t j = 0; j < board.cols; j++) {
                if (tryPlacingPiece(board, i, j, p)) {
                    auto newUnplaced = std::views::filter(unplaced, [p](Piece _p) { return !p.matches(_p); });

                    std::cout << "erasing " << k << "th piece with remaining pieces:\n";
                    displayPieceList(unplaced);

                    placePieces(board, newUnplaced);
                    ++splitCount;
                } else {
                }
            }
        }
        ++k;
    }

    if (splitCount == 1) {
        std::cout << "Adding puzle\n";
        solvedPuzzles.push_back(board);
    } else {
        std::cout << "not adding with split count=" << splitCount << "\n";
    }
}

bool PuzzleSolver::tryPlacingPiece(Puzzle& board, size_t row, size_t col, Piece piece) {
    std::cout << "try placing at (" << row << "," << col << ") " << piece.str() << " : ";
    if (!board(row, col).isPlaced) {
        std::cout << "available space : ";
        for (int i = 0; i < 4; i++) {
            std::cout << "rot " << i << ", ";
            if (board.fits(piece, row, col)) {
                board.place(piece, row, col);
                std::cout << "placing at (" << row << "," << col << ") : " << board(row, col).str() << "\n";
                return true;
            }
            piece.rotate();
        }
        std::cout << "no fit \n";
    } else {
        std::cout << "not available\n";
    }
    return false;
}

void PuzzleSolver::displayPieceList(std::ranges::input_range auto pieces) {
    for (auto p : pieces)
        std::cout << "• " << p.str() << "\n";
}
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>

#include "puzzlesolver.hpp"

PuzzleSolver::PuzzleSolver(Puzzle filledPuzzle)
    : initBoard(filledPuzzle.cols, filledPuzzle.rows, filledPuzzle.duplicationsAllowed, false),
      allPieces(filledPuzzle.pieces) {
}

void PuzzleSolver::findNewPuzzles() {
    std::cout << "Finding sollutions with " << allPieces.size() << "pieces and " << initBoard.cols << " by " << initBoard.rows << " board\n";

    placePieces(initBoard, allPieces);
    // removeDuplicatedPuzzles();
}

void PuzzleSolver::displaySolvedPuzzles() {
    for (auto puzzle : solvedPuzzles) {
        std::cout << "puzzle:\n";
        puzzle.display();
    }
    std::cout << solvedPuzzles.size() << " Solved puzles\n";
}

void PuzzleSolver::placePieces(Puzzle& board, std::vector<Piece>& unplaced) {
    // std::cout << "New branch with " << unplaced.size() << " pieces\n";
    int k = 0;
    for (Piece& p : unplaced) {
        // std::cout << "Picking up " << k << "th piece " << p.str() << "\n";
        for (size_t i = 0; i < board.rows; i++) {
            for (size_t j = 0; j < board.cols; j++) {
                // std::cout << "Looking at (" << i << ", " << j << "\n";

                if (board(i, j).isPlaced)
                    continue;

                Puzzle newBoard(board);
                if (tryPlacingPiece(newBoard, i, j, p)) {
                    std::vector<Piece> newUnplaced(unplaced);
                    newUnplaced.erase(newUnplaced.begin() + k);

                    // std::cout << "Remaining pieces:" << std::endl;
                    // displayPieceList(newUnplaced);

                    if (newUnplaced.size() == 0) {
                        // std::cout << "no more pieces\n";
                        if (!isAlreadyFound(newBoard)) {
                            std::cout << "Adding puzle" << std::endl;
                            solvedPuzzles.push_back(newBoard);
                        }
                        return;
                    } else {
                        placePieces(newBoard, newUnplaced);
                    }
                }
            }
        }
        ++k;
    }
}

bool PuzzleSolver::tryPlacingPiece(Puzzle& board, size_t row, size_t col, Piece piece) {
    // std::cout << "try placing: ";
    if (!board(row, col).isPlaced) {
        // std::cout << "available space : ";
        for (int i = 0; i < 4; i++) {
            // std::cout << "rot " << i << " " << piece.str() << ", ";
            if (board.fits(piece, row, col)) {
                board.place(piece, row, col);
                // std::cout << "placing at (" << row << "," << col << ") : " << board(row, col).str() << std::endl;
                return true;
            }
            piece.rotate();
        }
        // std::cout << "no fit \n";
    } else {
        // std::cout << "not available\n";
    }
    return false;
}

void PuzzleSolver::displayPieceList(const std::vector<Piece>& pieces) {
    for (auto p : pieces)
        std::cout << "• " << p.str() << "\n";
}

void PuzzleSolver::removeDuplicatedPuzzles() {
    for (auto pIt = solvedPuzzles.begin(); pIt < solvedPuzzles.end(); ++pIt) {
        for (auto pIt2 = pIt + 1; pIt2 < solvedPuzzles.end();) {
            if ((*pIt).matches(*pIt2)) {
                solvedPuzzles.erase(pIt2);
            } else
                ++pIt2;
        }
    }
}

bool PuzzleSolver::isAlreadyFound(const Puzzle& puzzle) {
    auto it = std::ranges::find_if(solvedPuzzles, [&puzzle](const Puzzle& p) { return puzzle.matchesAnyRotation(p); });
    return it != solvedPuzzles.end();
}
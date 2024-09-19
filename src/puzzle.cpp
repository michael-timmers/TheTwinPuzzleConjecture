#include <iostream>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t cols, size_t rows, int duplicationsAllowed)
    : rows(rows),
      cols(cols),
      duplicationsAllowed(duplicationsAllowed),
      pieces(rows * cols),
      jointCounts((rows * (cols - 1) + cols * (rows - 1)) / duplicationsAllowed) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            generateNextPiece(i, j);
            // std::cout << i << "," << j << ":" << (*this)(i, j).str() << std::endl;
        }
    }
}

bool Puzzle::fits(const Piece& p, size_t row, size_t col) {
    return (row == 0 || (*this)(row - 1, col).s.fits(p.n)) &&
           (col == cols - 1 || (*this)(row, col + 1).w.fits(p.e)) &&
           (row == rows - 1 || (*this)(row + 1, col).n.fits(p.s)) &&
           (col == 0 || (*this)(row, col - 1).e.fits(p.w));
}

void Puzzle::place(const Piece& p, size_t row, size_t col) {
    (*this)(row, col) = 0;
}

void Puzzle::display() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << (*this)(i, j).str() << " ";
        std::cout << std::endl;
    }
}

void Puzzle::generateNextPiece(int i, int j) {
    Piece& p = (*this)(i, j);
    p.n.jointID = (i == 0 ? 0 : -(*this)(i - 1, j).s.jointID);
    p.e.jointID = (j == cols - 1 ? 0 : getRandID());
    p.s.jointID = (i == rows - 1 ? 0 : getRandID());
    p.w.jointID = (j == 0 ? 0 : -(*this)(i, j - 1).e.jointID);
    p.isPlaced = false;
}

const int Puzzle::getRandID() {
    int ID = std::rand() % jointCounts.size() + 1;
    if (jointCounts[ID] == duplicationsAllowed)
        return getRandID();
    ++jointCounts[ID];
    return ID;
}
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
            (*this)(i, j) = generateNextPiece(i, j);
            // std::cout << i << "," << j << ":" << (*this)(i, j).str() << std::endl;
        }
    }
}

Piece& Puzzle::operator()(size_t row, size_t col) {
    assert(row < rows);
    assert(col < cols);
    return pieces[row * rows + col];
}

const Piece& Puzzle::operator()(size_t row, size_t col) const {
    assert(row < rows);
    assert(col < cols);
    return pieces[row * rows + col];
}

void Puzzle::display() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << (*this)(i, j).str() << " ";
        std::cout << std::endl;
    }
}
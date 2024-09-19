#include <iostream>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t cols, size_t rows, int duplicationsAllowed)
    : rows(rows),
      cols(cols),
      duplicationsAllowed(duplicationsAllowed),
      pieces(rows * cols),
      jointCounts((rows * (cols - 1) + cols * (rows - 1)) / duplicationsAllowed) {
    // need to seed puzle to generate joint ids
    (*this)(0, 0) = Piece(0, getRandID(), getRandID(), 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) j++;

            (*this)(i, j) = Piece(
                i == 0 ? 0 : -(*this)(i - 1, j).s.jointID,
                j == cols - 1 ? 0 : getRandID(),
                i == rows - 1 ? 0 : getRandID(),
                j == 0 ? 0 : -(*this)(i, j - 1).e.jointID);

            std::cout << i << "," << j << ":" << (*this)(i, j).str() << std::endl;
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
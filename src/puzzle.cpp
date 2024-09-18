#include <iostream>
#include <numeric>
#include <iterator>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t cols, size_t rows)
    : rows(rows),
      cols(cols),
      pieces(rows * cols) {
    // need to seed puzle to generate joint ids
    (*this)(0, 0) = Piece(0, 1, 2, 0);
    int ids = 3;  // since some IDDs have already been 'seeded'
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) j++;

            (*this)(i, j) = Piece(
                i == 0 ? 0 : -(*this)(i - 1, j).s.jointID,
                j == cols - 1 ? 0 : ids++,
                i == rows - 1 ? 0 : ids++,
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
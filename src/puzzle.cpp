#include <iostream>
#include <numeric>
#include <iterator>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t rows, size_t cols)
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
                i == 0 || i == rows - 1 ? 0 : -(*this)(i - 1, j).s.jointID,
                j == 0 || j == cols - 1 ? 0 : -(*this)(i, j - 1).w.jointID,
                i == rows - 1 ? 0 : ids++,
                j == 0 ? 0 : ids++);

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
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            std::cout << pieces[i][j].str() << " ";
        std::cout << std::endl;
    }
}
#pragma once

#include <vector>
#include <cassert>

#include "piece.hpp"

class Puzzle {
    size_t rows, cols;
    std::vector<Piece> pieces;

   public:
    Puzzle(size_t rows, size_t cols);

    Piece& operator()(size_t row, size_t col);
    const Piece& operator()(size_t row, size_t col) const;

    void display();
};
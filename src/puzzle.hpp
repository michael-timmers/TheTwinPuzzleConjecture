#pragma once

#include <vector>
#include <cassert>
#include <cstdlib>

#include "piece.hpp"

class Puzzle {
    size_t rows, cols;
    const int duplicationsAllowed;
    std::vector<Piece> pieces;
    std::vector<int> jointCounts;

   public:
    Puzzle(size_t cols, size_t rows, int duplicationsAllowed);

    inline Piece& operator()(size_t row, size_t col) {
        assert(row < rows);
        assert(col < cols);
        return pieces[row * rows + col];
    }

    inline const Piece& operator()(size_t row, size_t col) const {
        assert(row < rows);
        assert(col < cols);
        return pieces[row * rows + col];
    }

    void display();

   private:
    Piece generateNextPiece(int i, int j);

    const int getRandID();
};
#pragma once

#include <vector>
#include <cassert>
#include <cstdlib>

#include "piece.hpp"

class Puzzle {
    std::vector<int> jointCounts;

   public:
    size_t rows, cols;
    const int duplicationsAllowed;
    std::vector<Piece> pieces;

    Puzzle(size_t cols, size_t rows, int duplicationsAllowed, bool generatePieces = true);

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

    bool fits(const Piece& p, size_t row, size_t col);
    void place(const Piece& p, size_t row, size_t col);

    void display();

   private:
    void generateNextPiece(int i, int j);

    const int getRandID();
};
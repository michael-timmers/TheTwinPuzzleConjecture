#pragma once

#include <vector>
#include <cassert>
#include <cstdlib>

#include "piece.hpp"

class Puzzle;
class Puzzle {
    std::vector<int> jointCounts;

   public:
    size_t rows, cols;
    int duplicationsAllowed;
    std::vector<Piece> pieces;

    Puzzle(size_t cols, size_t rows, int duplicationsAllowed, bool generatePieces = true);

    // Puzzle(const Puzzle& other) : rows(other.rows), cols(other.cols), duplicationsAllowed(other.duplicationsAllowed), pieces(other.pieces) {}

    inline Piece& operator()(size_t row, size_t col) {
        assert(row < rows);
        assert(col < cols);
        return pieces[row * cols + col];
    }

    inline const Piece& operator()(size_t row, size_t col) const {
        assert(row < rows);
        assert(col < cols);
        return pieces[row * cols + col];
    }

    bool operator==(const Puzzle& other) const {
        for (auto p1 = pieces.begin(), p2 = other.pieces.begin(); p1 < pieces.end(); ++p1, ++p2) {
            if (!(*p1).matches(*p2))
                return false;
        }
        return true;
    }

    bool fits(const Piece& p, size_t row, size_t col);
    void place(const Piece& p, size_t row, size_t col);

    void display();

   private:
    void generateNextPiece(int i, int j);

    const int getRandID();
};
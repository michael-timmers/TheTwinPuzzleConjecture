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

    Puzzle(size_t rows, size_t cols, int duplicationsAllowed, bool generatePieces = true);

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

    bool matches(const Puzzle& other) const;
    bool matchesWithRotation(const Puzzle& other, int rot) const;
    bool matchesAnyRotation(const Puzzle& other) const;

    bool fits(const Piece& p, size_t row, size_t col) const;
    void place(const Piece& p, size_t row, size_t col);

    void display();

   private:
    void generateNextPiece(int i, int j);
    const int getRandID();

    int rotateRow(int row, int col, int rot) const;
    int rotateCol(int row, int col, int rot) const;
};
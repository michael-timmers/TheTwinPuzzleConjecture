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

    Piece& operator()(size_t row, size_t col);
    const Piece& operator()(size_t row, size_t col) const;

    void display();

   private:
    inline const int getRandID() {
        int ID = std::rand() % jointCounts.size() + 1;
        if (jointCounts[ID] == duplicationsAllowed)
            return getRandID();
        ++jointCounts[ID];
        return ID;
    }
};
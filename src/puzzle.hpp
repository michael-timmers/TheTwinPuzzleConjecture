#pragma once

#include <vector>

#include "piece.hpp"

class Puzzle {
    const int WIDTH, HEIGHT;
    std::vector<std::vector<Piece> > pieces;

   public:
    Puzzle(const int WIDTH, const int HEIGHT);

    void display();

   private:
    inline int lin2x(int i) const {
        return i % WIDTH;
    }

    inline int lin2y(int i) const {
        return i / HEIGHT;
    }
};
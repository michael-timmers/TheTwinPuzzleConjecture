#include <iostream>
#include <numeric>
#include <iterator>

#include "puzzle.hpp"

Puzzle::Puzzle(int WIDTH, int HEIGHT)
    : WIDTH(WIDTH),
      HEIGHT(HEIGHT),
      pieces(HEIGHT) {
    int ids = 3;
    for (int i = 0; i < HEIGHT; i++) {
        auto p = pieces[i].begin();
        for (int j = 0; j < WIDTH; j++, p++) {
            if (p->n.isEdge() && p->w.isEdge()) {
                pieces[i].push_back(Piece(0, 1, 2, 0));
            } else {
                pieces[i].push_back(Piece(
                    p.n.isEdge() || p.s.isEdge() ? 0 : -pieces[i - 1][j].s.jointID,
                    p.w.isEdge() || p.e.isEdge() ? 0 : -pieces[i][j - 1].w.jointID,
                    p.s.isEdge() ? 0 : ids++,
                    p.w.isEdge() ? 0 : ids++));
            }
            std::cout << i << "," << j << ":" << pieces[i][j].str() << std::endl;
        }
    }
}

void Puzzle::display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            std::cout << pieces[i][j].str() << " ";
        std::cout << std::endl;
    }
}
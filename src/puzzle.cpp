#include <iostream>
#include <numeric>
#include <iterator>

#include "puzzle.hpp"

Puzzle::Puzzle(int WIDTH, int HEIGHT)
    : WIDTH(WIDTH),
      HEIGHT(HEIGHT),
      pieces(HEIGHT) {
    // need to seed puzle to generate joint ids
    pieces[0].push_back(Piece(0, 1, 2, 0));
    int ids = 3;  // since some IDDs have already been 'seeded'
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; pieces[i].size() < WIDTH; j++) {
            pieces[i].push_back(Piece(
                i == 0 || i == HEIGHT - 1 ? 0 : -pieces[i - 1][j].s.jointID,
                j == 0 || j == WIDTH - 1 ? 0 : -pieces[i][j - 1].w.jointID,
                i == HEIGHT - 1 ? 0 : ids++,
                j == 0 ? 0 : ids++));
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
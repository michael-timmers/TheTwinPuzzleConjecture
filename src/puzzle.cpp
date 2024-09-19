#include <iostream>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t cols, size_t rows, int duplicationsAllowed)
    : rows(rows),
      cols(cols),
      duplicationsAllowed(duplicationsAllowed),
      pieces(rows * cols),
      jointCounts((rows * (cols - 1) + cols * (rows - 1)) / duplicationsAllowed) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*this)(i, j) = generateNextPiece(i, j);
            // std::cout << i << "," << j << ":" << (*this)(i, j).str() << std::endl;
        }
    }
}

void Puzzle::display() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << (*this)(i, j).str() << " ";
        std::cout << std::endl;
    }
}

Piece Puzzle::generateNextPiece(int i, int j) {
    return Piece(
        i == 0 ? 0 : -(*this)(i - 1, j).s.jointID,
        j == cols - 1 ? 0 : getRandID(),
        i == rows - 1 ? 0 : getRandID(),
        j == 0 ? 0 : -(*this)(i, j - 1).e.jointID);
}

const int Puzzle::getRandID() {
    int ID = std::rand() % jointCounts.size() + 1;
    if (jointCounts[ID] == duplicationsAllowed)
        return getRandID();
    ++jointCounts[ID];
    return ID;
}
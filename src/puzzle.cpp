#include <iostream>

#include "puzzle.hpp"

Puzzle::Puzzle(size_t cols, size_t rows, int duplicationsAllowed, bool generatePieces)
    : rows(rows),
      cols(cols),
      duplicationsAllowed(duplicationsAllowed),
      pieces(rows * cols),
      jointCounts((rows * (cols - 1) + cols * (rows - 1)) / duplicationsAllowed) {
    if (generatePieces) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                generateNextPiece(i, j);
                // std::cout << i << "," << j << ":" << (*this)(i, j).str() << std::endl;
            }
        }
    }
}

bool Puzzle::fits(const Piece& p, size_t row, size_t col) {
    // three cases where a edge can 'fit'
    // 1:is facing the edge of the puzzle [a'] and is a flat edge [b']
    // 2: is facing a piece [a], is a joint [b] and the other piece is unplaced [c']
    // 3:is facing a piece [a], the other peice is placed[c] and the joints match [d]
    // a'b'+abc'+acd

    bool nFits = (row == 0 && p.n.isEdge()) || (row != 0 && !p.n.isEdge() && !p.isPlaced) || (row != 0 && p.isPlaced && (*this)(row - 1, col).s.fits(p.n));
    bool eFits = (col == cols - 1 && p.e.isEdge()) || (col != cols - 1 && !p.e.isEdge() && !p.isPlaced) || (col != cols - 1 && p.isPlaced && (*this)(row, col + 1).w.fits(p.e));
    bool sFits = (row == rows - 1 && p.s.isEdge()) || (row != rows - 1 && !p.s.isEdge() && !p.isPlaced) || (row != rows - 1 && p.isPlaced && (*this)(row + 1, col).n.fits(p.s));
    bool wFits = (col == 0 && p.w.isEdge()) || (col != 0 && !p.w.isEdge() && !p.isPlaced) || (col != 0 && p.isPlaced && (*this)(row, col - 1).e.fits(p.w));

    std::cout << "edge checks: {" << nFits << " " << eFits << " " << sFits << " " << wFits << "}\n";
    return nFits && eFits && sFits && wFits;
}

void Puzzle::place(const Piece& p, size_t row, size_t col) {
    (*this)(row, col).setAll(p.n.jointID, p.e.jointID, p.s.jointID, p.w.jointID, true);
}

void Puzzle::display() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << (*this)(i, j).str() << " ";
        std::cout << std::endl;
    }
}

void Puzzle::generateNextPiece(int i, int j) {
    (*this)(i, j).n.jointID = (i == 0 ? 0 : -(*this)(i - 1, j).s.jointID);
    (*this)(i, j).e.jointID = (j == cols - 1 ? 0 : getRandID());
    (*this)(i, j).s.jointID = (i == rows - 1 ? 0 : getRandID());
    (*this)(i, j).w.jointID = (j == 0 ? 0 : -(*this)(i, j - 1).e.jointID);
    (*this)(i, j).isPlaced = false;
}

const int Puzzle::getRandID() {
    int ID = std::rand() % jointCounts.size() + 1;
    if (jointCounts[ID] == duplicationsAllowed)
        return getRandID();
    ++jointCounts[ID];
    return ID;
}
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

bool Puzzle::matches(const Puzzle& other) const {
    for (auto p1 = pieces.begin(), p2 = other.pieces.begin(); p1 < pieces.end(); ++p1, ++p2) {
        if (!(*p1).matches(*p2))
            return false;
    }
    return true;
}

bool Puzzle::matchesWithRotation(const Puzzle& other, int rot) const {
    // You can't rotate 90 or 270 deg if the puzzle is not a square
    if (rot % 2 == 1 && rows != cols)
        return false;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(*this)(rotateRow(i, j, rot), rotateCol(i, j, rot)).matches(other(i, j)))
                return false;
        }
    }
    return true;
}

bool Puzzle::matchesAnyRotation(const Puzzle& other) const {
    for (int rot = 0; rot < 4; rot++) {
        if (matchesWithRotation(other, rot))
            return true;
    }
    return false;
}

bool Puzzle::fits(const Piece& p, size_t row, size_t col) const {
    // three cases where a edge can 'fit'
    // 1:is facing the edge of the puzzle [a'] and is a flat edge [b']
    // 2: is facing a piece [a], is a joint [b] and the other piece is unplaced [c']
    // 3:is facing a piece [a], the other peice is placed[c] and the joints match [d]
    // a'b'+abc'+acd

    bool nFits = (row == 0 && p.n.isEdge()) || (row != 0 && !p.n.isEdge() && !p.isPlaced) || (row != 0 && p.isPlaced && (*this)(row - 1, col).s.fits(p.n));
    bool eFits = (col == cols - 1 && p.e.isEdge()) || (col != cols - 1 && !p.e.isEdge() && !p.isPlaced) || (col != cols - 1 && p.isPlaced && (*this)(row, col + 1).w.fits(p.e));
    bool sFits = (row == rows - 1 && p.s.isEdge()) || (row != rows - 1 && !p.s.isEdge() && !p.isPlaced) || (row != rows - 1 && p.isPlaced && (*this)(row + 1, col).n.fits(p.s));
    bool wFits = (col == 0 && p.w.isEdge()) || (col != 0 && !p.w.isEdge() && !p.isPlaced) || (col != 0 && p.isPlaced && (*this)(row, col - 1).e.fits(p.w));

    // std::cout << "edge checks: {" << nFits << " " << eFits << " " << sFits << " " << wFits << "}\n";
    return nFits && eFits && sFits && wFits;
}

void Puzzle::place(const Piece& p, size_t row, size_t col) {
    (*this)(row, col).setAll(p.n.jointID, p.e.jointID, p.s.jointID, p.w.jointID, true);
}

void Puzzle::display() {
    auto p = pieces.begin();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << p->str() << " ";
            ++p;
        }
        std::cout << std::endl;
    }
}

// Takes on the negative of the edges it shares with other pieces and randomly generates jointIDs for non placed pieces.
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

int mapRot2sin(int rot) {
    return (rot - 2) % 2;
}

int mapRot2cos(int rot) {
    return (rot - 1) % 2;
}

int Puzzle::rotateRow(int row, int col, int rot) const {
    int result = (row - (int)(rows) / 2) * mapRot2cos(rot) + (col - (int)(cols) / 2) * mapRot2sin(rot) + (int)rows / 2;
    return result;
}

int Puzzle::rotateCol(int row, int col, int rot) const {
    int result = (col - (int)cols / 2) * mapRot2cos(rot) - (row - (int)rows / 2) * mapRot2sin(rot) + (int)cols / 2;
    return result;
}
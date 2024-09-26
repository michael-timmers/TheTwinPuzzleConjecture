#pragma once

#include <string>

#include "edge.hpp"

class Piece {
   public:
    Edge n, e, s, w;
    bool isPlaced;

    Piece(int n = 0, int e = 0, int s = 0, int w = 0, bool isPlaced = false);

    inline std::string str() const {
        return "[" + std::to_string(isPlaced) + " " + n.str() + " " + e.str() + " " + s.str() + " " + w.str() + "]";
    }

    inline bool matches(const Piece& other) const {
        return n.matches(other.n) && e.matches(other.e) && s.matches(other.s) && w.matches(other.w) && isPlaced == other.isPlaced;
    }

    inline void setAll(int n, int e, int s, int w, bool isPlaced) {
        this->n.jointID = n;
        this->e.jointID = e;
        this->s.jointID = s;
        this->w.jointID = w;
        this->isPlaced = isPlaced;
    }

    inline void rotate() {
        n = w;
        e = n;
        s = e;
        w = s;
    }
};
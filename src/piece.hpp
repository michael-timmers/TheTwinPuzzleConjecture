#pragma once

#include <string>

#include "edge.hpp"

class Piece {
   public:
    Edge n, e, s, w;

    Piece(int n = 0, int e = 0, int s = 0, int w = 0);

    inline std::string str() const {
        return "[" + n.str() + " " + e.str() + " " + s.str() + " " + w.str() + "]";
    }

    inline void setAll(int n, int e, int s, int w) {
        this->n.jointID = n;
        this->e.jointID = e;
        this->s.jointID = s;
        this->w.jointID = w;
    }
};
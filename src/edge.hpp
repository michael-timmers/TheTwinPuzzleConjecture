#pragma once

#include <string>

class Edge {
   public:
    int jointID;

    Edge(int jointID);

    inline bool isEdge() const {
        return jointID == 0;
    }

    inline bool isMale() const {
        return jointID > 0;
    }

    inline std::string str() const {
        return std::to_string(jointID);
    }

    inline bool fits(const Edge& other) const {
        return jointID == -other.jointID;
    }

    inline bool matches(const Edge& other) const {
        return jointID == other.jointID;
    }
};

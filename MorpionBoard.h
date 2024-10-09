#pragma once
#include "Case.h"
#include <vector>

class CMorpionBoard {
    
    std::vector<std::vector<CMorpionCase>> _board;

public:

    CMorpionBoard(size_t x, size_t y);
    CMorpionCase getCase(size_t x, size_t y) const;
    void setCase(size_t x, size_t y, CMorpionCase c);
    bool isEmpty(size_t x, size_t y) const;
    CMorpionCase getWinner() const;

};
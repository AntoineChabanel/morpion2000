#pragma once
#include "MorpionBoard.h"
#include <vector>
#include "Vector2.h"
#include <string>
#include <array>

class CSituation {
    
    CMorpionBoard _board;

public:

    std::vector<CVector2> _poids;
    int IsSameBoard(CMorpionBoard toCompare)
    {
        return _board.isSameBoardClever(toCompare);
    }

    void setCase(size_t x, size_t y, CMorpionCase type)
    {
        _board.setCase(x, y, type);
    }

    CMorpionCase getCase(size_t x, size_t y) const
    {
        return _board.getCase(x,y);
    }
    bool isEmpty(size_t x, size_t y) const
    {
        return _board.isEmpty(x, y);
    }
    //TODO ! Constructeur à partir d'un fichier
    CSituation(std::string);
    CSituation(std::array<CMorpionCase, CMorpionBoard::sizeOfMap>);
};
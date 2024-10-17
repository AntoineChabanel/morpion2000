#pragma once
#include "Case.h"
#include <vector>
#include "MorpionBoard.h"
#include "RotationSymetrie.h"
#include <array>

class CMorpionBoard {
    
    std::vector<std::vector<CMorpionCase>> _board;

public:

    static const int sizeOfMap = 3;
    CMorpionBoard(size_t x, size_t y);
    CMorpionCase getCase(size_t x, size_t y) const;
    void setCase(size_t x, size_t y, CMorpionCase c);
    bool isEmpty(size_t x, size_t y) const;
    CMorpionCase getWinner() const;

    //Constructeur a partir d'un tableau de 9 cases
    CMorpionBoard(std::array<CMorpionCase,9>param)
    {
        _board.resize(3);
        for (int i = 0; i < 3; i++)
        {
            _board[i].resize(3);
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->setCase(i, j, param[(i * 3) + j]);
            }
        }
    }

    //Fonction qui retourne le board symetrique seulement pour un board de 3x3
    CMorpionBoard GetBoardSymetrie();

    //Fonction valable pour un board 3x3 uniquement retourne le meme board mais avec une rot de 90 deg a droite
    CMorpionBoard GetBoard90DgrDroite();

    //La fonction retourne un objet qui contient les infos sur la transformation que la grille a du subir pour être identique et si elle est identique
    CRotationSymetrie isSameBoardVeryClever(CMorpionBoard toCompare);

    //La fonction retourne -1 si les grilles sont diff�rentes, 0 si elles sont identiques, 1 si il a fallu tourner la grille toCompare une fois de 90 degr�s � droite, 2 si a fallu la tourner 2 fois et 3 si il a fallu la tourner 3 fois, si on la tourne 4 fois on retomberait sur la m�me grille
    int isSameBoardClever(CMorpionBoard toCompare);
    
    //Comparaison stupide case par case
    bool isSameBoardDumb(CMorpionBoard toCompare);
};
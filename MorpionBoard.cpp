#include "MorpionBoard.h"

CMorpionBoard::CMorpionBoard(size_t x, size_t y):
    _board(x, std::vector<CMorpionCase>(y))
{
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            _board[i][j] = CMorpionCase::Empty;
        }
    }
}

CMorpionCase CMorpionBoard::getCase(size_t x, size_t y) const
{
    return _board[x][y];
}

void CMorpionBoard::setCase(size_t x, size_t y, CMorpionCase c)
{
    _board[x][y] = c;
}

bool CMorpionBoard::isEmpty(size_t x, size_t y) const
{
    return _board[x][y] == CMorpionCase::Empty;
}

CMorpionCase CMorpionBoard::getWinner() const
{
    // Check rows
    for (size_t i = 0; i < _board.size(); i++) {
        if (_board[i][0] != CMorpionCase::Empty && _board[i][0] == _board[i][1] && _board[i][0] == _board[i][2]) {
            return _board[i][0];
        }
    }
    // Check columns
    for (size_t i = 0; i < _board[0].size(); i++) {
        if (_board[0][i] != CMorpionCase::Empty && _board[0][i] == _board[1][i] && _board[0][i] == _board[2][i]) {
            return _board[0][i];
        }
    }
    // Check diagonals
    if (_board[0][0] != CMorpionCase::Empty && _board[0][0] == _board[1][1] && _board[0][0] == _board[2][2]) {
        return _board[0][0];
    }
    if (_board[0][2] != CMorpionCase::Empty && _board[0][2] == _board[1][1] && _board[0][2] == _board[2][0]) {
        return _board[0][2];
    }
    return CMorpionCase::Empty;
}

CMorpionBoard CMorpionBoard::GetBoard90DgrDroite()
{
    CMorpionBoard otherBoard = { sizeOfMap, sizeOfMap };
    otherBoard.setCase(0, 2, this->getCase(0, 0));
    otherBoard.setCase(1, 2, this->getCase(0, 1));
    otherBoard.setCase(2, 2, this->getCase(0, 2));
    otherBoard.setCase(0, 1, this->getCase(1, 0));
    otherBoard.setCase(1, 1, this->getCase(1, 1));
    otherBoard.setCase(2, 1, this->getCase(1, 2));
    otherBoard.setCase(0, 0, this->getCase(2,0));
    otherBoard.setCase(1, 0, this->getCase(2, 1));
    otherBoard.setCase(2, 0, this->getCase(2, 2));
    return otherBoard;
}

CMorpionBoard CMorpionBoard::GetBoardSymetrie()
{
    CMorpionBoard otherBoard = { sizeOfMap, sizeOfMap };
    return CMorpionBoard();
}

CRotationSymetrie CMorpionBoard::isSameBoardVeryClever(CMorpionBoard toCompare)
{
    if (this->isSameBoardClever(toCompare) != -1)
    {
        return { true,this->isSameBoardClever(toCompare),false };
    }
    else
    {

    }
}



int CMorpionBoard::isSameBoardClever(CMorpionBoard toCompare)
{
    int nbRot = 0;
    if (this->isSameBoardDumb(toCompare))
    {
        return 0;
    }
    else
    {
        nbRot = 1;
        CMorpionBoard toCompareWithRot = toCompare;
        toCompareWithRot = toCompare.GetBoard90DgrDroite();
        if (this->isSameBoardDumb(toCompareWithRot))
        {
            return nbRot;
        }
        else
        {
            nbRot = 2;
            toCompareWithRot = toCompareWithRot.GetBoard90DgrDroite();
            if (this->isSameBoardDumb(toCompareWithRot))
            {
                return nbRot;
            }
            else
            {
                nbRot = 3;
                toCompareWithRot = toCompareWithRot.GetBoard90DgrDroite();
                if (this->isSameBoardDumb(toCompareWithRot))
                {
                    return nbRot;
                }
                else
                {
                    //On a tout essay� mais il ne sont d�finitivement pas identiques
                    return -1;
                }
            }
        }
    }
}

bool CMorpionBoard::isSameBoardDumb(CMorpionBoard toCompare)
{
    bool same = true;
    for (int i = 0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            //Pour chaque case du tableau
            if (this->getCase(i, j) != toCompare.getCase(i, j))
            {
                same = false;
                break;
                //Dommage on ne sort pas de la boucle des i, il faudrait utiliser "go_to" ?
            }
        }
    }
    return same;
}

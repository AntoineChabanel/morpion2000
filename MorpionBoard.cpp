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
#include <iostream>
#include "MorpionBoard.h"

int main()
{
    CMorpionBoard board(3, 3);
    board.setCase(0, 0, CMorpionCase::Cross);
    board.setCase(1, 1, CMorpionCase::Cross);
    board.setCase(2, 2, CMorpionCase::Cross);
    std::cout << "Winner: " << static_cast<int>(board.getWinner()) << std::endl;
    return 0;
}

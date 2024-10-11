#include <iostream>
#include "MorpionBoard.h"
#include "Situation.h"

int main()
{
    CMorpionBoard board(3, 3);
    board.setCase(0, 0, CMorpionCase::Cross);
    board.setCase(1, 1, CMorpionCase::Cross);
    board.setCase(2, 2, CMorpionCase::Cross);
    std::cout << "Winner: " << static_cast<int>(board.getWinner()) << std::endl;

    //Générer toutes les situations possibles
    std::vector<CSituation> toutesLesSituations = { };
    const int nbValeursDifferentes = 3;
    int lastCombination = 000000000;
    while (lastCombination != 222222222)
    {

    }
    

    return 0;
}

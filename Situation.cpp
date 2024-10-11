#include "Situation.h"
#include <fstream>
#include "MorpionBoard.h"
#include <array>

//Les fichiers sont composés d'un caractère par ligne, 0 = croix, 1 = rond, 2 = vide
//Une fois qu'on a décrit la grille, on décrit les poids (un chiffre par ligne)
//En tout il y a 18 lignes, on décrit d'abord la première ligne de gauche à droite, puis la deuxieme ligne
CSituation::CSituation(std::string nomFichier)
    :_board(CMorpionBoard::sizeOfMap,CMorpionBoard::sizeOfMap)
{
    std::ifstream fichier(nomFichier);  // Ouvre le fichier
    if (!fichier)
    {  // Vérifie si le fichier est bien ouvert
        std::cerr << "Impossible d'ouvrir le fichier!" << std::endl;
        EXIT_FAILURE;
    }

    for (int i = 0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            int nbLu;
            fichier >> nbLu;
            if (nbLu == 0)
            {
                _board.setCase(i, j, CMorpionCase::Cross);
            }
            else if (nbLu == 1)
            {
                _board.setCase(i, j, CMorpionCase::Circle);
            }
            else if (nbLu == 2)
            {
                _board.setCase(i, j, CMorpionCase::Empty);
            }
        }
    }
    fichier.close();  // Fermer le fichier
}

CSituation::CSituation(std::array<CMorpionCase, CMorpionBoard::sizeOfMap> param)
    :_board(CMorpionBoard::sizeOfMap, CMorpionBoard::sizeOfMap)
{
    for (int i=0;i<CMorpionBoard::sizeOfMap;i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            this->setCase(i, j, param[(i * CMorpionBoard::sizeOfMap) + j]);
        }
    }
}

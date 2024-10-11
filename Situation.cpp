#include "Situation.h"
#include <fstream>
#include "MorpionBoard.h"
#include <array>

//Les fichiers sont compos�s d'un caract�re par ligne, 0 = croix, 1 = rond, 2 = vide
//Une fois qu'on a d�crit la grille, on d�crit les poids (un chiffre par ligne)
//En tout il y a 18 lignes, on d�crit d'abord la premi�re ligne de gauche � droite, puis la deuxieme ligne
CSituation::CSituation(std::string nomFichier)
    :_board(CMorpionBoard::sizeOfMap,CMorpionBoard::sizeOfMap)
{
    std::ifstream fichier(nomFichier);  // Ouvre le fichier
    if (!fichier)
    {  // V�rifie si le fichier est bien ouvert
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

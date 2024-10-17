#pragma once
#include "MorpionBoard.h"
#include <vector>
#include "Vector2.h"
#include <string>
#include <array>
#include <random>

class CSituation {
    
    CMorpionBoard _board;
    
public:
    CVector2 derniereCaseJoue = { -1, -1 };
    std::vector<CVector2> _poids;
    //Premier élément : nom de la case de 0 à 8, 0 = A1 1=A2,...
    //Deuxieme élément : poids en lui même (int)
    CRotationSymetrie IsSameBoard(CMorpionBoard toCompare)
    {
        return _board.isSameBoardVeryClever(toCompare);
    }
    
    //On donne en param la case dans laquelle l'IA joue et les infos sur la rotation qui a été appliqué au board original pour qu'on détecte qu'il s'agit en fait des mêmes boards
    CVector2 GetCoFromBoardWithoutRotation(CVector2, CRotationSymetrie);

    //Utile pour la fonction au dessus
    CVector2 GetCoOfAfterRotLeft(CVector2 entree);

    //Utile pour la fonction au dessus
    CVector2 GetCoOfAfterSymetrie(CVector2 entree);

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
    CSituation(std::array<CMorpionCase, 9>);
    //Constructeur à partir d'un fichier
    CSituation(std::string);
    //Enregistreur dans un fichier
    void EnregistrerDansFichier(std::string);

    //On demande le coup à jouer dans cette situation, elle retourne la coordonnée ou elle joue
    CVector2 QuelCoupJouer(CRotationSymetrie RotationPourTrouverQueCetteGrilleEstIdentique);
    void PunirPourLeDernierCoupJoue();
    void RecompenserPourLeDernierCoupJoue();
    void LeDernierCoupJoueAConduitAUneEgalite();
    void victoireImmediateSurLeDernierCoupJoue();
};
#include "Situation.h"
#include <fstream>
#include "MorpionBoard.h"
#include <array>
#include <random>

//Les fichiers sont composés d'un caractère par ligne, 1 = croix, 2 = rond, 0 = vide
//Une fois qu'on a décrit la grille, on décrit les poids (un chiffre par ligne)
//En tout il y a 18 lignes, on décrit d'abord la première ligne de gauche à droite, puis la deuxieme ligne. -1 au poid quand le coup n'est pas jouable
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
    for (int i = 0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            int nbLu;
            fichier >> nbLu;
            _poids.push_back({ (i * 3) + j,nbLu });
        }
    }
    fichier.close();  // Fermer le fichier
}

void CSituation::EnregistrerDansFichier(std::string nomFich)
{
    std::ofstream fichier(nomFich,std::ofstream::out);
    if (!fichier.is_open())
        std::cerr << "erreur dans l ecriture du fichier de poids\n";
    for (int i = 0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            if (this->getCase(i, j) == CMorpionCase::Empty)
            {
                fichier << 0 << std::endl;
            }
            if (this->getCase(i, j) == CMorpionCase::Cross)
            {
                fichier << 1 << std::endl;
            }
            if (this->getCase(i, j) == CMorpionCase::Circle)
            {
                fichier << 2 << std::endl;
            }
        }
    }
    for (int i = 0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            if (this->getCase(i, j) != CMorpionCase::Empty)
            {
                fichier << -1 << std::endl;
            }
            else
            {
                //Vérifier que le vector contient au moins l'élément avec l'index qu'on veut accéder
                if (_poids.size() <= ((i * 3) + j))
                {
                    std::cerr << "Il y a un probleme lors de l acces a un poids type 0\n";
                    EXIT_FAILURE;
                }
                else
                {
                    if (_poids[(i * 3) + j].GetX() == (i * 3) + j)
                    {
                        fichier << _poids[(i * 3) + j].GetY() << std::endl;
                    }
                    else
                    {
                        std::cerr << "Il y a un probleme lors de l acces a un poids type 1\n";
                        EXIT_FAILURE;
                    }
                }
            }
        }
    }
}

void CSituation::PunirPourLeDernierCoupJoue()
{
    if (derniereCaseJoue.GetX() == -1)
    {
        std::cerr << "Tu as essayé de me punir ou me récompenser mais je n'ai jamais joue";
    }
    //On ajoute une bille
    _poids[(derniereCaseJoue.GetX() * 3) + derniereCaseJoue.GetY()].SetY(_poids[(derniereCaseJoue.GetX() * 3) + derniereCaseJoue.GetY()].GetY() - 1);
}

void CSituation::RecompenserPourLeDernierCoupJoue()
{
    if (derniereCaseJoue.GetX() == -1)
    {
        std::cerr << "Tu as essayé de me punir ou me récompenser mais je n'ai jamais joue";
    }
    //On ajoute une bille
    _poids[(derniereCaseJoue.GetX() * 3) + derniereCaseJoue.GetY()].SetY(_poids[(derniereCaseJoue.GetX() * 3) + derniereCaseJoue.GetY()].GetY() + 1);
}

void CSituation::LeDernierCoupJoueAConduitAUneEgalite()
{
    if (derniereCaseJoue.GetX() == -1)
    {
        std::cerr << "Tu as essayé de me punir ou me récompenser mais je n'ai jamais joue";
    }
    //il ne se passe rien
}

void CSituation::victoireImmediateSurLeDernierCoupJoue()
{
    if (derniereCaseJoue.GetX() == -1)
    {
        std::cerr << "Tu as essayé de me punir ou me récompenser mais je n'ai jamais joue";
    }
    //On ajoute un milliard de billes au coup gagnant et on vide les autres
    for (int i = 0; i < 9; i++)
    {
        _poids[i].SetY(0);
    }
    _poids[(derniereCaseJoue.GetX() * 3) + derniereCaseJoue.GetY()].SetY(10);
}

CVector2 CSituation::GetCoFromBoardWithoutRotation(CVector2 CoDemandeDansLaGrilleOriginale, CRotationSymetrie RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation)
{
    if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation.symetrie)
    {
        if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 0)
        {
            return this->GetCoOfAfterSymetrie(CoDemandeDansLaGrilleOriginale);
        }
        else if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 1)
        {
            return this->GetCoOfAfterSymetrie(this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale));
        }
        else if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 2)
        {
            return this->GetCoOfAfterSymetrie(this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale)));
        }
        else
        {
            return this->GetCoOfAfterSymetrie(this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale))));
        }
    }
    else
    {
        if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 0)
        {
            return CoDemandeDansLaGrilleOriginale;
        }
        else if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 1)
        {
            return this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale);
        }
        else if (RotationPourPasserDeGrilleOriginaleAGrilleCommeSituation._nbRot == 2)
        {
            return this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale));
        }
        else
        {
            return this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(this->GetCoOfAfterRotLeft(CoDemandeDansLaGrilleOriginale)));
        }
    }
}

CVector2 CSituation::GetCoOfAfterRotLeft(CVector2 entree)
{
    if (entree.GetY() == 0)
    {
        if (entree.GetX() == 0)
        {
            return { 2,0 };
        }
        else if (entree.GetX() == 1)
        {
            return { 2,1 };
        }
        else if (entree.GetX() == 2)
        {
            return { 2,2 };
        }
        else
            return{ -1,-1 };
    }
    else if (entree.GetY() == 1)
    {
        if (entree.GetX() == 0)
        {
            return { 1,0 };
        }
        else if (entree.GetX() == 1)
        {
            return { 1,1 };
        }
        else if (entree.GetX() == 2)
        {
            return { 1,2 };
        }
        else
            return{ -1,-1 };
    }
    else if (entree.GetY() == 2)
    {
        if (entree.GetX() == 0)
        {
            return { 0,0, };
        }
        else if (entree.GetX() == 1)
        {
            return { 0,1 };
        }
        else if (entree.GetX() == 2)
        {
            return { 0,2 };
        }
        else
            return{ -1,-1 };
    }
    else
        return{ -1,-1 };
}

CVector2 CSituation::GetCoOfAfterSymetrie(CVector2 entree)
{
    if (entree.GetY() == 0)
    {
        if (entree.GetX() == 0)
        {
            return { 2,0 };
        }
        else if (entree.GetX() == 1)
        {
            return { 1,0 };
        }
        else if (entree.GetX() == 2)
        {
            return { 0,0 };
        }
        else
            return { -1,-1 };
    }
    else if (entree.GetY() == 1)
    {
        if (entree.GetX() == 0)
        {
            return { 2,1 };
        }
        else if (entree.GetX() == 1)
        {
            return { 1,1 };
        }
        if (entree.GetX() == 2)
        {
            return { 0,1 };
        }
        else
            return { -1,-1 };
    }
    else if (entree.GetY() == 2)
    {
        if (entree.GetX() == 0)
        {
            return { 2,2 };
        }
        else if (entree.GetX() == 1)
        {
            return { 1,2 };
        }
        else if (entree.GetX() == 2)
        {
            return { 0,2 };
        }
        else
            return { -1,-1 };
    }
    else
        return { -1,-1 };

}

CSituation::CSituation(std::array<CMorpionCase, 9> param)
    :_board(CMorpionBoard::sizeOfMap, CMorpionBoard::sizeOfMap)
{
    for (int i=0;i<CMorpionBoard::sizeOfMap;i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            this->setCase(i, j, param[(i * CMorpionBoard::sizeOfMap) + j]);
        }
    }
    
    for (int i=0; i < CMorpionBoard::sizeOfMap; i++)
    {
        for (int j = 0; j < CMorpionBoard::sizeOfMap; j++)
        {
            if (this->getCase(i, j) != CMorpionCase::Empty)
            {
                _poids.push_back({(i * 3) + j, -1});
            }
            else
            {
                _poids.push_back({(i * 3) + j, 0 });
            }
        }
    }
}

CVector2 CSituation::QuelCoupJouer(CRotationSymetrie RotationPourTrouverQueCetteGrilleEstIdentique)
{
    int sommePoids = 0;
    for (int i = 0; i < 9; i++)
    {
        sommePoids += _poids[i].GetY();
    }
    std::uniform_int_distribution<> distrib(0, sommePoids);
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomNumber = distrib(gen);
    //Voir a quelle bille correspond le numero qu'on vient de tirer
    int i = 0;
    sommePoids = _poids[i].GetY();
    while (sommePoids <= randomNumber)
    {
        i++;
        sommePoids += _poids[i].GetY();
    }
    if (i != _poids[i].GetX())
    {
        std::cerr << "erreur bizarre hehe \n";
    }
    int partieEntiere = i / 3;
    return GetCoFromBoardWithoutRotation({ i % 3,partieEntiere },RotationPourTrouverQueCetteGrilleEstIdentique);
}
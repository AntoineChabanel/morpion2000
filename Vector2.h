#include <iostream>

class CVector2{  
    int x;
    int y;

public:

    int GetX() {return x;}
    int GetY() {return y;}
    void SetX(int newX) { x = newX;}
    void SetY(int newY) { y = newY;}

    CVector2(int xToSet,int yToSet)
    {
        /*if (xToSet >= taillePlateau)*/
            x = xToSet;
        /*else
        {
            x = taillePlateau;
            std::cerr << "Tentative d acces a une case en dehors du plateau";
        }*/
        /*if (yToSet >= taillePlateau)*/
            y = yToSet;
        /*else
        {
            y = taillePlateau;
            std::cerr << "Tentative d acces a une case en dehors du plateau";
        }*/
    }
};
#include "perso.h"
perso_t* initPac_man(int ** plateau, int w, int h){
    perso_t* Pac_man = malloc(sizeof(perso_t));
    Pac_man->id=99;
    Pac_man->etat=0;
    coordPlat(plateau, w, h, Pac_man->id, &Pac_man->posX, &Pac_man->posY);
    return Pac_man;
}


void movePacman(int ** plateau, perso_t* Pac_man,int* mort, int direction, SDL_Rect* rectPac)
{
    if (movePossible(plateau, Pac_man->posX, Pac_man->posY, direction))
                {
                    switch (direction)
                    {
                    case 1:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 1, mort);
                        rectPac->y = rectPac->y + rectPac->h;
                        Pac_man->etat = 3;
                        break;
                    case 3:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 3, mort);
                        rectPac->y = rectPac->y - rectPac->h;
                        Pac_man->etat = 1;
                        break;
                    case 4:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 4, mort);
                        rectPac->x = rectPac->x + rectPac->w;
                        Pac_man->etat = 0;
                        break;
                    case 2:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 2, mort);
                        rectPac->x = rectPac->x - rectPac->w;
                        Pac_man->etat = 2;
                        break;
                    default:
                        break;
                    }
                }
}
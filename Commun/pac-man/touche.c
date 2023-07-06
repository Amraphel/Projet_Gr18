#include "touche.h"

int deplacement(int move, perso_t *Pac_man, int **plateau, SDL_Rect **tabRectPerso, perso_t **tabPerso, int nbFan, SDL_Rect rectPac, int w, int h, int pause, int keyPressed)
{
    int direction;
    int dir;
    switch (move)
    {
    case 4:
        dir = 4;
        break;
    case 3:
        dir = 3;
        break;
    case 2:
        dir = 2;
        break;
    case 1:
        dir = 1;
        break;

    default:
        break;
    }

    if (collision(rectPac, tabRectPerso, nbFan, tabPerso) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
    {
        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, dir, Pac_man->id, &Pac_man->super) && !keyPressed)
        {
            direction = dir;
        }
    }

    return direction;
}

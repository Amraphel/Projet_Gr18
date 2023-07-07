#include "touche.h"

/**
 * @brief déplace un personnage dans le plateau selon la direction demandée
 * @param [in] move déplacement demandé 
 * @param [in] Pac_man perso_t de pac-man
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] tabRectPerso tableau contenant les SDl_Rect des personnages du jeu
 * @param [in] tabPerso tableau contenant les perso_t des personnages du jeu
 * @param [in] nbFan nombre de fantomes
 * @param [in] rectPac SDL_Rect de pac-man
 * @param [in] w nombre de colonnes du plateau 
 * @param [in] h nombre de lignes du plateau
 * @param [in] pause int indiquant si le jeu est en pause
 * @param [in] keyPressed indicateur de si une touche du clavier a été pressée
 * @return direction que prend le personnage
 */ 
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

/**
 * @brief met ou enlève la pause
 * @param [in] pause int indiquant si le jeu est en pause
 * @return pause
 */ 
int enPause(int pause)
{
    if (pause == 1)
    {
        pause = 2;
    }
    else
    {
        pause = 1;
    }
    return pause;
}

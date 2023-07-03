#include "regleInky.h"

void modifRegle(regles_t **tabRegle, int nbRegle, int nbContrainte)
{
    int numRegle = rand() % nbRegle;
    int numContrainte = rand() % nbContrainte;
    int nouvC = 0;
    switch (numContrainte)
    {
    case 0: // case_ t droite de -1 à 3
        nouvC = rand() % 5 - 1;
        tabRegle[numRegle]->droite = nouvC;
        break;
    case 1: // case_ t haut
        nouvC = rand() % 5 - 1;
        tabRegle[numRegle]->haut = nouvC;
        break;
    case 2: // case_ t gauche
        nouvC = rand() % 5 - 1;
        tabRegle[numRegle]->gauche = nouvC;
        break;
    case 3: // case_ t bas
        nouvC = rand() % 5 - 1;
        tabRegle[numRegle]->bas = nouvC;
        break;

    case 4: // distance_t distance_fantome
        nouvC = rand() % 5;
        tabRegle[numRegle]->distance_fantome = nouvC;
        break;
    case 5: // distance_t distance_pacman
        nouvC = rand() % 5;
        tabRegle[numRegle]->distance_pacman = nouvC;
        break;

    case 6: // cadran_t cadran_fantome
    nouvC = rand() % 4;
    tabRegle[numRegle]->cadran_fantome = nouvC;
        break;
    case 7: // cadran_t cadran_pacman
        nouvC = rand() % 4;
        tabRegle[numRegle]->cadran_pacman = nouvC;
        break;

    case 8: // int priorite
        nouvC = rand() % 6;
        tabRegle[numRegle]->priorite = nouvC;
        break;

    case 9: // action_t action
        nouvC = rand() % 4;
        tabRegle[nbRegle]->action = nouvC;
        break;

    default:
        break;
    }
}

//void initCervau(int nbRegle, int nbContrainte)
//{

//}
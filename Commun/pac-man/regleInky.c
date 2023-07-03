#include "regleInky.h"

void modifRegle(regles_t **tabRegle, int nbRegle, int nbContrainte)
{
    int numRegle = rand() % nbRegle;
    int numContrainte = rand() % nbContrainte;
    int nouvC = 0;
    switch (numContrainte)
    {
    case 0: // case_ t droite de -1 à 3
    case 1: // case_ t haut
    case 2: // case_ t gauche
    case 3: // case_ t bas
        nouvC = rand() % 5 -1;
        break;

    case 4: // distance_t distance_fantome
    case 5: // distance_t distance_pacman
        nouvC = rand() % 5;
        break;

    case 6: // cadran_t cadran_pacman
    case 7: // cadran_t cadran_pacman
        nouvC = rand() % 4;
        break;

    case 8: // int priorite
        nouvC = rand() % 6;
        break;

    case 9: // action_t action
        nouvC = rand() % 4;
        break;

    default:
        break;
    }
    tabRegle[numRegle][numContrainte] = nouvC;
}

void initCervau(int nbRegle, int nbContrainte)
{

}
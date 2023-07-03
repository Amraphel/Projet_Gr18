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
    tabRegle[numRegle]->dir_fantome = nouvC;
        break;
    case 7: // cadran_t cadran_pacman
        nouvC = rand() % 4;
        tabRegle[numRegle]->dir_pacman = nouvC;
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

regles_t** initCervau(int nbRegle, int nbContrainte)
{
    regles_t** tabRegle = malloc(sizeof(regles_t)*nbRegle);
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        tabRegle[i]->droite = -1;
        tabRegle[i]->haut = -1;
        tabRegle[i]->gauche = -1;
        tabRegle[i]->bas = -1;
        tabRegle[i]->distance_fantome = -1;
        tabRegle[i]->distance_pacman = -1;
        tabRegle[i]->dir_fantome = -1;
        tabRegle[i]->dir_pacman = -1;
        tabRegle[i]->priorite = 0;
        tabRegle[i]->action = i;
    }
    for(i; i < nbRegle; i++)
    {
        tabRegle[i]->droite = rand() % 5 - 1;
        tabRegle[i]->haut = rand() % 5 - 1;
        tabRegle[i]->gauche = rand() % 5 - 1;
        tabRegle[i]->bas = rand() % 5 - 1;
        tabRegle[i]->distance_fantome = rand() % 5;
        tabRegle[i]->distance_pacman = rand() % 5;
        tabRegle[i]->dir_fantome = rand() % 4;
        tabRegle[i]->dir_pacman = rand() % 4;
        tabRegle[i]->priorite = rand() % 6;
        tabRegle[i]->action = rand() % 4;
    }
    return tabRegle;
}

void freeCerveau(regles_t** tabRegle, int nbRegle)
{
    int i = 0;
    for(i; i<nbRegle; i++)
    {
        free(tabRegle[i]);
    }
    free(tabRegle);
}
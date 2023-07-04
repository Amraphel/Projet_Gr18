#include "regleInky.h"

void modifRegle(regles_t *regle, int numContrainte, int valeur)
{
    switch (numContrainte)
    {
    case 0: // case_ t droite de -1 à 3
        regle->droite =valeur;
        break;
    case 1: // case_ t haut
        regle->haut = valeur;
        break;
    case 2: // case_ t gauche
        regle->gauche = valeur;
        break;
    case 3: // case_ t bas
        regle->bas =valeur;
        break;

    case 4: // distance_t distance_fantome
        regle->distance_fantome = valeur;
        break;
    case 5: // distance_t distance_pacman
        regle->distance_pacman = valeur;
        break;

    case 6: // cadran_t cadran_fantome
        regle->dir_fantome = valeur;
        break;
    case 7: // cadran_t cadran_pacman
        regle->dir_pacman = valeur;
        break;

    case 8: // int priorite
        regle->priorite = valeur;
        break;

    case 9: // action_t action
        regle->action = valeur;
        break;

    default:
        break;
    }
}

int possibilite(int numContrainte)
{
    int possible = 0;
    switch (numContrainte)
    {
    case 0: // case_ t droite de -1 à 3
    case 1:
    case 2:
    case 3: // case_ t bas
        possible = 5;
        break;

    case 4: // distance_t distance_fantome
    case 5:
        possible = 6;
        break;
    case 6:
    case 7:
        possible = 5;
        break; // case_ t haut
    case 8:
        possible = 6;
        break; // case_ t haut
    case 9:    // action_t action
        possible = 4;
        break; // case_ t haut

    default:
        break;
    }
    return possible;
}

void initCerveau(regles_t **tabRegle, int nbRegle)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        tabRegle[i]->droite = -1;
        tabRegle[i]->haut = -1;
        tabRegle[i]->gauche = -1;
        tabRegle[i]->bas = -1;
        tabRegle[i]->distance_fantome = -1;
        tabRegle[i]->distance_pacman = -1;
        tabRegle[i]->dir_fantome = -1;
        tabRegle[i]->dir_pacman = -1;
        tabRegle[i]->priorite = 1;
        tabRegle[i]->action = i + 1;
    }
    for (i = 4; i < nbRegle; i++)
    {
        tabRegle[i]->droite = rand() % 5 - 1;
        tabRegle[i]->haut = rand() % 5 - 1;
        tabRegle[i]->gauche = rand() % 5 - 1;
        tabRegle[i]->bas = rand() % 5 - 1;
        tabRegle[i]->distance_fantome = rand() % 5;
        tabRegle[i]->distance_pacman = rand() % 5;
        tabRegle[i]->dir_fantome = rand() % 4;
        tabRegle[i]->dir_pacman = rand() % 4;
        tabRegle[i]->priorite = rand() % 6 + 1;
        tabRegle[i]->action = rand() % 4 + 1;
    }
}

void freeCerveau(regles_t **tabRegle, int nbRegle)
{
    int i = 0;
    for (i = 0; i < nbRegle; i++)
    {
        free(tabRegle[i]);
        tabRegle[i]=NULL;
    }
    free(tabRegle);
    tabRegle=NULL;
}


int * createListePos(int nbPos){
    int * listpost= malloc(sizeof(int)*nbPos);
    for(int i=0; i<nbPos; i++){
        listpost[i]=i-1;
    }   
    return listpost;
}
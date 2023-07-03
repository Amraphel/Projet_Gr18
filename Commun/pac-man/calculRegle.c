#include "calculRegle.h"

int compareRegle(regles_t *regleOrigin, regles_t *etatPlateau)
{
    int i = 0;
    if (regleOrigin->gauche != -1 && regleOrigin->gauche != etatPlateau->gauche)
    {
        i = 1;
    }
    if (regleOrigin->haut != -1 && regleOrigin->haut != etatPlateau->haut)
    {
        i = 1;
    }
    if (regleOrigin->bas != -1 && regleOrigin->bas != etatPlateau->bas)
    {
        i = 1;
    }
    if (regleOrigin->droite != -1 && regleOrigin->droite != etatPlateau->droite)
    {
        i = 1;
    }
    if (regleOrigin->dir_fantome != -1 && regleOrigin->dir_fantome != etatPlateau->dir_fantome)
    {
        i = 1;
    }
    if (regleOrigin->dir_pacman != -1 && regleOrigin->dir_pacman != etatPlateau->dir_pacman)
    {
        i = 1;
    }
    if (regleOrigin->distance_fantome != -1 && regleOrigin->distance_fantome != etatPlateau->distance_fantome)
    {
        i = 1;
    }
    if (regleOrigin->distance_pacman != -1 && regleOrigin->distance_pacman != etatPlateau->distance_pacman)
    {
        i = 1;
    }
    return i;
}

regles_t *calculEtat(int **plateau, perso_t **tabPerso, int w, int h)
{
    regles_t *etat = malloc(sizeof(regles_t));
    if (etat)
    {
        etat->action = 0;
        etat->priorite = 0;

        // Détermination de la distance de Pacman par rapport au fantome
        int dPac = pow(tabPerso[0]->posX - tabPerso[2]->posX, 2) + pow(tabPerso[0]->posY - tabPerso[2]->posY, 2);
        if (dPac < pow(w / 5, 2))
        {
            etat->distance_pacman = TP;
        }
        else if (dPac < pow(2 * w / 5, 2))
        {
            etat->distance_pacman = P;
        }
        else if (dPac < pow(3 * w / 5, 2))
        {
            etat->distance_pacman = AP;
        }
        else if (dPac < pow(4 * w / 5, 2))
        {
            etat->distance_pacman = L;
        }
        else
        {
            etat->distance_pacman = TL;
        }

        // Détermination de la distance de Pac par rapport à l'autre fantome
        int dPacFan = pow(tabPerso[0]->posX - tabPerso[1]->posX, 2) + pow(tabPerso[0]->posY - tabPerso[1]->posY, 2);
        if (dPacFan < pow(w / 5, 2))
        {
            etat->distance_fantome = TP;
        }
        else if (dPacFan < pow(2 * w / 5, 2))
        {
            etat->distance_fantome = P;
        }
        else if (dPacFan < pow(3 * w / 5, 2))
        {
            etat->distance_fantome = AP;
        }
        else if (dPacFan < pow(4 * w / 5, 2))
        {
            etat->distance_fantome = L;
        }
        else
        {
            etat->distance_fantome = TL;
        }

        //Calcul de la direction où se trouve Pacman
        if (abs(tabPerso[2]->posX - tabPerso[0]->posX) < abs(tabPerso[2]->posY - tabPerso[0]->posY))
        {
            if (tabPerso[2]->posX - tabPerso[0]->posX < 0)
            {
                etat->dir_pacman = E;
            }
            else
            {
                etat->dir_pacman = O;
            }
        }
        else
        {
            if (tabPerso[2]->posY - tabPerso[0]->posY < 0){
                etat->dir_pacman=S;
            } else{
                etat->dir_pacman=N;
            }
        }

        //Calcul de la direction où se trouve le fantôme
        if (abs(tabPerso[2]->posX - tabPerso[1]->posX) < abs(tabPerso[2]->posY - tabPerso[1]->posY))
        {
            if (tabPerso[2]->posX - tabPerso[1]->posX < 0)
            {
                etat->dir_fantome = E;
            }
            else
            {
                etat->dir_fantome = O;
            }
        }
        else
        {
            if (tabPerso[2]->posY - tabPerso[1]->posY < 0){
                etat->dir_fantome=S;
            } else{
                etat->dir_fantome=N;
            }
        }
    }
}
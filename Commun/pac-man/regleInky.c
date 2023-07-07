#include "regleInky.h"

/**
 * @brief modifie des règles
 * @param [in] regle règle à modifier
 * @param [in] numContrainte numéro de la contrainte
 * @param [in] valeur nouvelle valeur
 */ 
void modifRegle(regles_t *regle, int numContrainte, int valeur)
{
    switch (numContrainte)
    {
    case 0: // case_ t droite de -1 à 3
        regle->droite = valeur;
        break;
    case 1: // case_ t haut
        regle->haut = valeur;
        break;
    case 2: // case_ t gauche
        regle->gauche = valeur;
        break;
    case 3: // case_ t bas
        regle->bas = valeur;
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

/**
 * @brief donne le nobre de possiblités pour une contrainte
 * @param [in] numContrainte numéro de la contrainte
 * @return le nombre de possibilités
 */ 
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

/**
 * @brief initialise un tableau de règles
 * @param [in] tabRegle tableau de règles
 * @param [in] nbRegle nombre de règle
 */ 
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
        tabRegle[i]->priorite = 0;
        tabRegle[i]->action = i + 1;
    }
    for (int i = 4; i < 8; i++)
    {
        tabRegle[i]->droite = -1;
        tabRegle[i]->haut = -1;
        tabRegle[i]->gauche = -1;
        tabRegle[i]->bas = -1;
        switch (i)
        {
        case 4:
            tabRegle[i]->droite = 1;
            tabRegle[i]->dir_pacman = 1;
            tabRegle[i]->action = 1;
            break;
        case 5:
            tabRegle[i]->haut = 1;
            tabRegle[i]->dir_pacman = 0;
            tabRegle[i]->action = 2;
            break;
        case 6:
            tabRegle[i]->gauche = 1;
            tabRegle[i]->dir_pacman = 3;
            tabRegle[i]->action = 3;
            break;
        case 7:
            tabRegle[i]->bas = 1;
            tabRegle[i]->dir_pacman = 2;
            tabRegle[i]->action = 4;
            break;
        default:
            break;
        }
        tabRegle[i]->distance_fantome = -1;
        tabRegle[i]->distance_pacman = -1;
        tabRegle[i]->dir_fantome = -1;
        tabRegle[i]->priorite = 4;
    }
    for (i = 8; i < nbRegle; i++)
    {
        int random = rand() % 100;
        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->droite = -1;
        }
        else
        {
            tabRegle[i]->droite = rand() % 4;
        }
        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->haut = -1;
        }
        else
        {
            tabRegle[i]->haut = rand() % 4;
        }
        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->gauche = -1;
        }
        else
        {
            tabRegle[i]->gauche = rand() % 4;
        }
        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->bas = -1;
        }
        else
        {
            tabRegle[i]->bas = rand() % 4;
        }
        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->distance_fantome = -1;
        }
        else
        {
            tabRegle[i]->distance_fantome = rand() % 5;
        }

        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->distance_pacman = -1;
        }
        else
        {
            tabRegle[i]->distance_pacman = rand() % 5;
        }

        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->dir_fantome = -1;
        }
        else
        {
            tabRegle[i]->dir_fantome = rand() % 4;
        }

        random = rand() % 100;
        if (random < 70)
        {
            tabRegle[i]->dir_pacman = -1;
        }
        else
        {
            tabRegle[i]->dir_pacman = rand() % 4;
        }

        tabRegle[i]->priorite = rand() % 5 + 1;
        tabRegle[i]->action = rand() % 4 + 1;
    }
}

/**
 * @brief libère le tableau de règles
 * @param [in] tabRegle tableau de règles
 * @param [in] nbRegle nombre de règles
 */ 
void freeCerveau(regles_t **tabRegle, int nbRegle)
{
    int i = 0;
    for (i = 0; i < nbRegle; i++)
    {
        free(tabRegle[i]);
        tabRegle[i] = NULL;
    }
    free(tabRegle);
    tabRegle = NULL;
}

/**
 * @brief créer une liste de possibilités
 * @param [in] nbPos nombre de possibilités
 * @param [in] numContrainte numéro de la contrainte
 * @return une liste de possibilités
 */ 
int *createListePos(int nbPos, int numContrainte)
{
    int *listpost = malloc(sizeof(int) * nbPos);
    for (int i = 0; i < nbPos; i++)
    {
        if (numContrainte == 8)
        {
            listpost[i] = i;
        }
        else
        {
            listpost[i] = i - 1;
        }
    }
    return listpost;
}
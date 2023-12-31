#include "perso.h"

/**
 * @brief initialisation du perso pac man
 * @param [in] plateau plateau du jeu
 * @param [in] w coordonnee sur la longueur
 * @param [in] h coordonne sur la largeur
 * @return un perso_t pac man
 */
perso_t *initPac_man(int **plateau, int w, int h)
{
    perso_t *Pac_man = malloc(sizeof(perso_t));
    if (Pac_man == NULL)
    {
        printf("Erreur de malloc Pac_man\n");
        exit(EXIT_FAILURE);
    }
    Pac_man->id = 99;
    Pac_man->etat = 0;
    Pac_man->super = 0;
    coordPlat(plateau, w, h, Pac_man->id, &Pac_man->posX, &Pac_man->posY);
    return Pac_man;
}

/**
 * @brief deplacement de pac man dans le jeu attention matrice transposee
 * @param [in] plateau du jeu (matrice)
 * @param [in] Pac_man perso pour recuperer ses info
 * @param [in] direction dans laquel il va
 * @return
 *      - 0 bas
 *      - 1 gauche
 *      - 2 haut
 *      - 3 droite
 */
int movePacman(int **plateau, perso_t *Pac_man, int direction)
{
    if (movePossible(plateau, Pac_man->posX, Pac_man->posY, direction))
    {
        switchDirection(direction, Pac_man);
    }
    return direction;
}

/**
 * @brief deplacement de pac man dans le jeu attention matrice transposee
 * @param [in] plateau du jeu (matrice)
 * @param [in] Pac_man perso pour recuperer ses info
 * @param [in] direction dans laquel il va
 * @return
 *      - 0 bas
 *      - 1 gauche
 *      - 2 haut
 *      - 3 droite
 */
int heuriBasiquePac(int **plateau, int x, int y, int dir, int ite)
{
    int newHeuri = 0;
    if (ite > 0)
    {
        for (int j = 1; j < 5; j++)
        {
            if (j != dir && movePossible(plateau, x, y, j))
            {
                switch (j)
                {
                case 1:
                    newHeuri += heuriBasiquePac(plateau, (x + 1) % 23, y, 3, ite - 1) / 2;
                    break;
                case 2:
                    newHeuri += heuriBasiquePac(plateau, x, (y - 1 + 23) % 23, 4, ite - 1) / 2;
                    break;
                case 3:
                    newHeuri += heuriBasiquePac(plateau, (x - 1 + 23) % 23, y, 1, ite - 1) / 2;
                    break;
                case 4:
                    newHeuri += heuriBasiquePac(plateau, x, (y + 1) % 23, 2, ite - 1) / 2;
                    break;

                default:
                    break;
                }
            }
        }
    }

    if (plateau[x][y] > 100)
    {
        newHeuri = newHeuri - plateau[x][y];
    }
    else
    {
        newHeuri = newHeuri + plateau[x][y] + 1;
    }
    return newHeuri;
}

/**
 * @brief deplacement automatique (IA) de pacman
 * @param [in] plateau du jeu (matrice)
 * @param [in] Pac_man perso pour recuperer ses info
 * @return
 *      la direction dans lequel il doit aller
 *      - 0
 *      - 1
 *      - 2
 *      - 3
 */
int movePacmanIA(int **plateau, perso_t *Pac_man)
{
    // fprintf(stderr, "movePac\n");
    int dir = 0;
    int heuri = -1;
    int i = rand() % 4 + 1;
    for (int j = 1; j < 5; j++)
    {
        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, i))
        {
            int newHeuri = 0;
            switch (i)
            {
            case 1:
                newHeuri += heuriBasiquePac(plateau, Pac_man->posX + 1, Pac_man->posY, 3, 3);
                break;
            case 2:
                newHeuri += heuriBasiquePac(plateau, Pac_man->posX, Pac_man->posY - 1, 4, 3);
                break;
            case 3:
                newHeuri += heuriBasiquePac(plateau, Pac_man->posX - 1, Pac_man->posY, 1, 3);
                break;
            case 4:
                newHeuri += heuriBasiquePac(plateau, Pac_man->posX, Pac_man->posY + 1, 2, 3);
                break;

            default:
                break;
            }
            if (Pac_man->super == 0)
            {
                if ((heuri == -1) || newHeuri > heuri)
                {
                    heuri = newHeuri;
                    dir = i;
                }
            }
            if (Pac_man->super == 1)
            {
                if ((heuri == -1) || newHeuri < heuri)
                {
                    heuri = newHeuri;
                    dir = i;
                }
            }
        }
        i = (i + 1) % 5;
        if (i == 0)
        {
            i++;
        }
    }
    switchDirection(dir, Pac_man);

    return dir;
}

/**
 * @brief tourne pac-man dans la direction vers laquelle il va
 * @param [in] direction direction que prend pac-man
 * @param [in] Pac_man personnage à tourner
 */
void switchDirection(int direction, perso_t *Pac_man)
{
    switch (direction)
    {
    case 1:
        Pac_man->etat = 3;
        break;
    case 3:
        Pac_man->etat = 1;
        break;
    case 4:
        Pac_man->etat = 0;
        break;
    case 2:
        Pac_man->etat = 2;
        break;
    default:
        break;
    }
}

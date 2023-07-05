#include "plateau.h"

/**
 * REVIEW
 * Pourquoi ne pas avoir créé une structure coordinates_t pour stocker et renvoyer les coordonnées ?
 *
 * @brief trouve les coordonnées dans le plateau d'un objet d'id val
 * @param [in] plateau matrice contenant les id de tous les objets du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @param [in] val id de l'objet dont on cherche les coordonnées
 * @param [in] x numéro de la ligne où se trouve l'objet recherché
 * @param [in] y colonne où se trouve l'objet recherché
 */
void coordPlat(int** plateau, int w, int h, int val, int* x, int* y)
{
    *x = 0;
    *y = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (plateau[i][j] == val)
            {
                *x = i;
                *y = j;
            }
        }
    }
}

/**
 * @brief allocation de l'espace nécessaire pour construire le plateau
 * @param [in] width largeur du plateau (nombre de colonnes)
 * @param [in] height hauteur du plateau (nombre de lignes)
 * @return un tableau d'int
 */
int** create_plateau(int width, int height)
{
    int** plateau = malloc(sizeof(int*) * width);
    if (plateau == NULL)
    {
        fprintf(stderr, "create_plateau : erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < width; i++)
    {
        // REVIEW : calloc initialise tout à 0, donc pas besoin de le faire manuellement
        int* ligne = calloc(height, sizeof(int));
        if (ligne == NULL)
        {
            fprintf(stderr, "create_plateau : erreur d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }

        plateau[i] = ligne;
    }
    return plateau;
}

/**
 * @brief affichage du plateau dans le terminal
 * @param [in] mat plateau à afficher
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 */
void printPlateau(int** mat, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            fprintf(stderr, "%d ", mat[i][j]);
        }
        fprintf(stderr, "\n");
    }
}


/**
 * @brief création d'un plateau et insertion des valeurs contenues dans un fichier texte
 * @param [in] lvl fichier texte contenant les valeurs à insérer dans le plateau
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return un tableau de valeurs
 */
int** loadPlateau(char* lvl, int* w, int* h)
{
    int** plateau = NULL;
    FILE* file = fopen(lvl, "r");
    if (file)
    {
        fscanf(file, "%d %d\n", w, h);

        plateau = create_plateau(*w, *h);
        for (int i = 0; i < *w; i++)
        {
            for (int j = 0; j < *h; j++)
            {
                fscanf(file, "%d ", &plateau[i][j]);
            }
            fscanf(file, "\n");
        }
        // printPlateau(plateau, *w, *h);
    }
    fclose(file);
    return plateau;
}


/**
 * @brief vérifie qu'un mouvement pécifique est possible dans une position donnée
 * @param [in] plateau tableau contenant les id de plusieurs objets
 * @param [in] xPerso numéro de la ligne où se trouve le personnage à déplacer
 * @param [in] yPerso numéro de la colonne où se trouve le personnage à déplacer
 * @param [in] direction direction dans laquelle on veut faire aller le personnage
 * @param [in] id id du personnage à déplacer
 * @param [in] super indicateur de si Pac-man est en mode super Pac-man
 * @return
 *       -0 si le mouvement n'est pas possible
 *       -1 si le mouvement est possible
 */
int movePossible(int** plateau, int xPerso, int yPerso, int direction, int id, int* super)
{
    int DeplacementPossible = 0;
    int xd, yh, xg, yb;
    int plat = 0;
    switch (direction)
    {
    case 1: // droite
        xd = xPerso + 1;
        plat = plateau[xd][yPerso];
        if (plat == 0 || plat == -1 || plat >= 150 || plat == 99 || plat == 20)
        {
            DeplacementPossible = 1;
            if (plat == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;

    case 2: // haut
        yh = yPerso - 1;
        plat = plateau[xPerso][yh];
        if (plat == 0 || plat == -1 || plat >= 150 || plat == 99 || plat == 20)
        {
            DeplacementPossible = 1;
            if (plat == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;

    case 3: // gauche
        xg = xPerso - 1;
        plat = plateau[xg][yPerso];
        if (plat == 0 || plat == -1 || plat >= 150 || plat == 99 || plat == 20)
        {
            DeplacementPossible = 1;
            if (plat == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;
    case 4: // bas
        yb = yPerso + 1;
        plat = plateau[xPerso][yb];
        if (plat == 0 || plat == -1 || plat >= 150 || plat == 99 || plat == 20)
        {
            DeplacementPossible = 1;
            if (plat == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;
    default:
        break;
    }
    return DeplacementPossible;
}


/**
 * @brief vérifie si le mouvement demandé est possible et si oui déplace l'id du personnage dans le tableau vers l'endroit demandé
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] xPerso numéro de la ligne où se trouve le personnage à déplacer
 * @param [in] yPerso numéro de la colonne où se trouve le personnage à déplacer
 * @param [in] idPerso id du personnage à déplacer
 * @param [in] direction direction dans laquelle on veut déplacer le personnage
 * @param [in] mort valeur qui indique si Pac-man est vivant ou non
 * @param [in] super valeur qui indique si Pac-man est en mode super Pac-man
 */
void movePersoInPlateau(int** plateau, int* xPerso, int* yPerso, int idPerso, int direction, int* mort, int* super)
{

    int xDeplacement = *xPerso;
    int yDeplacement = *yPerso;

    if (movePossible(plateau, *xPerso, *yPerso, direction, idPerso, super) == 1)
    {

        switch (direction)
        {
        case 1: // droite
            xDeplacement = *xPerso + 1;
            break;
        case 2: // haut
            yDeplacement = *yPerso - 1;
            break;
        case 3: // gauche
            xDeplacement = *xPerso - 1;
            break;
        case 4: // bas
            yDeplacement = *yPerso + 1;
            break;

        default:
            break;
        }

        if (xDeplacement == 11 && yDeplacement == -1)
        {
            yDeplacement = 22;
        } else if (xDeplacement == 11 && yDeplacement == 23)
        {
            yDeplacement = 0;
        }

        if (idPerso == 99)
        {

            plateau[*xPerso][*yPerso] = -1;
            plateau[xDeplacement][yDeplacement] = 99;
        } else
        {
            if (idPerso != 99 && *super == 0)
            {
                if (plateau[xDeplacement][yDeplacement] == 99 && *super == 0)
                {
                    *mort = 1;
                }
                plateau[*xPerso][*yPerso] -= idPerso;
                plateau[xDeplacement][yDeplacement] += idPerso;
            }
        }
        *xPerso = xDeplacement;
        *yPerso = yDeplacement;
    }
}

//cette fonction vérifie s'il reste encore des pac-gommes, comme les pac-gommes sont sur les cases qui valent 0
/**
 * @brief vérifie s'il reste des pac-gommes
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return
 *       -0 s'il reste au moins une pac-gomme
 *       -autre chose s'il n'y a plus de pac-gommes
 */
int gom_exist(int** plateau, int w, int h)
{
    int rep = 1;
    int i = 0;
    int j = 0;

    while (i < w && rep != 0)
    {
        while (j < h && rep != 0)
        {
            rep = plateau[i][j];
            j++;
        }
        i++;
        j = 0;
    }

    return rep;
}

/**
 * @brief sauvegarde l'état actuel du tableau dans un fichier texte
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 */
void savePlateau(int** plateau, int w, int h)
{
    FILE* file = fopen("./source/save.txt", "w");
    fprintf(file, "%d %d\n", w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            fprintf(file, "%d ", plateau[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/**
 * @brief libère l'espace alloué pour le plateau
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 */
void freePlateau(int** plateau, int w)
{
    for (int i = 0; i < w; i++)
    {
        free(plateau[i]);
        plateau[i] = NULL;
    }
    free(plateau);
}

/**
 * @brief donne à super la valeur 1 indiquant que Pac-man est en mode super Pac-man
 * @param [in] id id du personnage
 * @param [in] super valeur indiquant si Pac-man est en mode super Pac-man ou non
 */
void etatSuperPac(int id, int* super)
{
    if (id == 99 && *super == 0)
    {
        *super = 1;
    }
}
#include "fantome.h"

/**
 * @brief initialisation du fantome blinky
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return fantome blinky
 */ 
perso_t *initBlinky(int **plateau, int w, int h)
{
    perso_t *blinky = malloc(sizeof(perso_t));
    if(blinky == NULL)
    {
        printf("Erreur de malloc blinky\n");
        exit(EXIT_FAILURE);
    }
    blinky->id = 200;
    blinky->super = 0;
    coordPlat(plateau, w, h, blinky->id, &blinky->posX, &blinky->posY);
    blinky->coordX=blinky->posX;
    blinky->coordY=blinky->posY;
    return blinky;
}

/**
 * @brief initialisation du fantome clyde
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return fantome clyde
 */ 
perso_t *initClyde(int **plateau, int w, int h)
{
    perso_t *clyde = malloc(sizeof(perso_t));
    if(clyde == NULL)
    {
        printf("Erreur de malloc clyde\n");
        exit(EXIT_FAILURE);
    }
    clyde->id = 210;
    clyde->super = 0;
    coordPlat(plateau, w, h, clyde->id, &clyde->posX, &clyde->posY);
    clyde->coordX=clyde->posX;
    clyde->coordY=clyde->posY;
    return clyde;
}

/**
 * @brief initialisation du fantome Inky
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return fantome Inky
 */ 
perso_t *initInky(int **plateau, int w, int h)
{
    perso_t *inky = malloc(sizeof(perso_t));
    if(inky == NULL)
    {
        printf("Erreur de malloc inky\n");
        exit(EXIT_FAILURE);
    }
    inky->id = 220;
    inky->super = 0;
    coordPlat(plateau, w, h, inky->id, &inky->posX, &inky->posY);
    inky->coordX=inky->posX;
    inky->coordY=inky->posY;
    return inky;
}

/**
 * @brief initialisation du fantome Pinky
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @return fantome Pinky
 */ 
perso_t *initPinky(int **plateau, int w, int h)
{
    perso_t *pinky = malloc(sizeof(perso_t));
    if(pinky == NULL)
    {
        printf("Erreur de malloc pinky\n");
        exit(EXIT_FAILURE);
    }
    pinky->id = 230;
    pinky->super = 0;
    coordPlat(plateau, w, h, pinky->id, &pinky->posX, &pinky->posY);
    pinky->coordX=pinky->posX;
    pinky->coordY=pinky->posY;
    return pinky;
}


/**
 * @brief créer une heuristique pour trouver un chemin le plus court possible entre un fantome et Pac-man
 * @param [in] heuri tableau contenant l'heuristique des cases du plateau
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] x ligne de départ de l'heuristique
 * @param [in] y colonne de départ de l'heuristique
 * @param [in] val valeur d'heuristique de la case de départ
 */ 
void creerHeuri(int **heuri, int **plateau, int x, int y, int val)
{
    heuri[x][y] = val;
    for (int i = 1; i < 5; i++)
    {
        int newX = x;
        int newY = y;
        if (movePossible(plateau, x, y, i, -1, NULL))
        {
            switch (i)
            {
            case 1:
                newX = (newX+1)%23;

                break;
            case 2:
                newY = (newY-1+23)%23;
                break;
            case 3:
                newX = (newX-1+23)%23;
                break;
            case 4:
                newY = (newY+1)%23;
                break;

            default:
                break;
            }
            if (heuri[newX][newY] == -1 || heuri[newX][newY] > val + 1)
            {
                creerHeuri(heuri, plateau, newX, newY, val + 1);
            }
        }
    }
}

/**
 * @brief 
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] pacX  ligne où se trouve pac-man
 * @param [in] pacY colonne où se trouve pac-man
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 */ 
int **heuristique(int **plateau, int pacX, int pacY, int w, int h)
{
    int **heuri = malloc(sizeof(int *) * w);
    if(heuri == NULL)
    {
        printf("Erreur de malloc heuri\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < w; i++)
    {
        int *ligne = malloc(sizeof(int) * h);
        if(ligne == NULL)
    {
        printf("Erreur de malloc ligne\n");
        exit(EXIT_FAILURE);
    }
        heuri[i] = ligne;
        for (int j = 0; j < h; j++)
        {
            heuri[i][j] = -1;
        }
    }
    creerHeuri(heuri, plateau, pacX, pacY, 0);
    return heuri;
}

/**
 * @brief 
 * @param [in] heuri
 * @param [in] w
 */ 
void freeHeuri(int **heuri, int w)
{
    for (int i = 0; i < w; i++)
    {
        free(heuri[i]);
    }
    free(heuri);
}

/**
 * @brief trouve le prochain déplacement à faire pour le fantome 
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] heuristique tableau contenant les valeurs d'heuristique des cases du plateau
 * @param [in] fantX numéro de la ligne sur laquelle se trouve le fantome
 * @param [in] fantY numéro de la colonne sur laquelle se trouve le fantome
 * @param [in] pacman structure du personnage Pac-man
 * @return 
 *       -1 pour aller à droite
 *       -2 pour aller en haut
 *       -3 pour aller à gauche
 *       -4 pour aller en bas
 */ 
int getNextMove(int **plateau, int **heuristique, int fantX, int fantY, perso_t * pacman)
{
    int dir = 0;
    int heuri = -1;
    for (int i = 1; i < 5; i++)
    {
        if (movePossible(plateau, fantX, fantY, i, -1, NULL))
        {
            int newHeuri = 0;
            switch (i)
            {
            case 1:
                newHeuri = heuristique[(fantX + 1)%23][fantY];
                break;
            case 2:
                newHeuri = heuristique[fantX][(fantY - 1+23)%23];
                break;
            case 3:
                newHeuri = heuristique[(fantX - 1+23)%23][fantY];
                break;
            case 4:
                newHeuri = heuristique[fantX][(fantY + 1)%23];
                break;

            default:
                break;
            }
            if (pacman->super==0)
            {
                if (heuri == -1 || heuri > newHeuri)
                {
                    heuri = newHeuri;
                    dir = i;
                }
            }
            if (pacman->super==1)
            {
                if (heuri ==-1 || heuri < newHeuri)
                {
                    heuri = newHeuri;
                    dir =i ;
                }
            }
        }
    }
    return dir;
}

/**
 * @brief déplacer clyde de façon aléatoire
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] window fenêtre d'affichage
 * @param [in] Clyde structure du personnage clyde
 * @return 
 *       -1 pour aller à droite
 *       -2 pour aller en haut
 *       -3 pour aller à gauche
 *       -4 pour aller en bas
 */ 
int moveRandom(int **plateau, SDL_Window* window, perso_t *Clyde)
{
    int i = rand() % 4 + 1;
    SDL_Rect
        window_dimensions = {0};
    SDL_GetWindowSize(window,
                      &window_dimensions.w,
                      &window_dimensions.h);
    while (!movePossible(plateau, Clyde->posX, Clyde->posY, i, Clyde->id, &Clyde->super))
    {
        i = rand() % 4 + 1;
    }

    {
        switch (i)
        {
        case 1:
            Clyde->etat=3;
            break;
        case 2:
            Clyde->etat=2;
            break;
        case 3:
            Clyde->etat=1;
            break;
        case 4:
            Clyde->etat=0;
            break;

        default:
            break;
        }
    }
    return i;
}

// fonction blinky : plus court chemin vers pac-man
/**
 * @brief déplace Blinky dans la direction du plus court chemin trouvé
 * @param [in] window fenêtre d'affichage
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @param [in] Blinky structure du personnage blinky
 * @param [in] Pac_man structure du personnage Pac-man
 * @return 
 *       -1 pour aller à droite
 *       -2 pour aller en haut
 *       -3 pour aller à gauche
 *       -4 pour aller en bas
 */ 
int moveBlinky( SDL_Window *window,int **plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man)
{
    SDL_Rect
        window_dimensions = {0};

    int **heuri = heuristique(plateau, Pac_man->posX, Pac_man->posY, w, h);

    SDL_GetWindowSize(window,
                      &window_dimensions.w,
                      &window_dimensions.h);

    int move = getNextMove(plateau, heuri, Blinky->posX, Blinky->posY, Pac_man);
    switch ((move))
    {
    case 1:
        // movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 1, mort);
        
        Blinky->etat=3;
        break;
    case 2:
        // movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 2, mort);
        
        Blinky->etat=2;
        break;

    case 3:
        // movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 3, mort);
        Blinky->etat=1;
        break;
    case 4:
        // movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 4, mort);
        
        Blinky->etat=0;
        break;

    default:
        break;
    }

    freeHeuri(heuri,w);
    return move;
}

/**
 * @brief déplace clyde dans la direction du plus court chemin trouvé et parfois dans une direction aléatoire
 * @param [in] window fenêtre d'affichage
 * @param [in] plateau tableau contenant les id des objets et des personnages du jeu
 * @param [in] w largeur du plateau (nombre de colonnes)
 * @param [in] h hauteur du plateau (nombre de lignes)
 * @param [in] Clyde structure du personnage clyde
 * @param [in] Pac_man structure du personnage Pac-man
 * @return 
 *       -1 pour aller à droite
 *       -2 pour aller en haut
 *       -3 pour aller à gauche
 *       -4 pour aller en bas
 */ 
int moveClyde(SDL_Window *window, int **plateau, int w, int h, perso_t *Clyde, perso_t *Pac_man)
{
    int dir;
    int i=rand()%100 +1;
    if(i<50){
        dir=moveRandom(plateau,window,Clyde);
    } else{
        dir=moveBlinky(window,plateau,w,h,Clyde, Pac_man);
    }
    return dir;

}

int moveInky(SDL_Window *window, int **plateau, int w, int h, perso_t* Inky, perso_t *Pac_man)
{
    int dir;
    dir=moveClyde(window,plateau,w,h,Inky, Pac_man);
    return dir;
}

int movePinky(SDL_Window *window, int **plateau, int w, int h, perso_t* Pinky, perso_t *Pac_man)
{
    int dir;
    dir=moveClyde(window,plateau,w,h,Pinky, Pac_man);
    return dir;
}

/**
 * @brief fait réapparaître un fantome après qu'il soit tué
 * @param [in] tempsMortFantome temps pendant lequel le fantome est mort
 * @param [in] tabPerso tableau qui contient tous les personnages
 * @param [in] nbFan nombre de fantomes
 */ 
void reapparitionFantome(int* tempsMortFantome, perso_t** tabPerso, int nbFan, SDL_Rect **rectFan, int* dir)
{
    int i;
    for(i = 1; i<=nbFan; i++)
    {
        if(tempsMortFantome[i-1]>=250)
        {
            tabPerso[i]->super = 0;
            tempsMortFantome[i-1]=0;
            tabPerso[i]->posX = tabPerso[i]->coordX;
            tabPerso[i]->posY = tabPerso[i]->coordY;
            rectFan[i]->x = rectFan[i]->w*tabPerso[i]->coordY;
            rectFan[i]->y = rectFan[i]->h*tabPerso[i]->coordX;
            dir[i]=0;
        }
    }
}
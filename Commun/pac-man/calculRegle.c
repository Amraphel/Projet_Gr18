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

regles_t *calculEtat(int **tableau, perso_t **tabPerso, int w, int idFantome)
{
    int idAutreFant = 0;
    int distFant = 1000;
    int xFant = tabPerso[idFantome]->posX;
    int yFant = tabPerso[idFantome]->posY;
    int caseX = xFant;
    int caseY = yFant;
    for (int i = 1; i < 5; i++)
    {
        if (i != idFantome)
        {
            int dist = pow(tabPerso[idFantome]->posX - tabPerso[i]->posX, 2) + pow(tabPerso[idFantome]->posY - tabPerso[i]->posY, 2);
            if (dist < distFant)
            {
                idAutreFant = i;
                distFant = dist;
            }
        }
    }
    regles_t *etat = malloc(sizeof(regles_t));
    if (etat)
    {
        etat->action = 0;
        etat->priorite = 0;
        for (int i = 1; i < 5; i++)
        {
            switch (i)
            {
            case 1:
                caseX = xFant + 1;
                caseY = yFant;
                break;
            case 2:
                caseX = xFant;
                caseY = yFant - 1;
                break;
            case 3:
                caseX = xFant - 1;
                caseY = yFant;
                break;
            case 4:
                caseX = xFant;
                caseY = yFant + 1;
                break;
            default:
                break;
            }
            int val;
            if (tableau[caseX][caseY] == 99)
            {
                val = PACMAN;
            }
            else if (tableau[caseX][caseY] == 0 || (tableau[caseX][caseY] == -1))
            {
                val = VIDE;
            }
            else if (tableau[caseX][caseY] < 50)
            {
                val = MUR;
            }
            else
            {
                val = FANTOME;
            }

            switch (i)
            {
            case 1:
                etat->droite = val;
                break;
            case 2:
                etat->haut = val;
                break;
            case 3:
                etat->gauche = val;
                break;
            case 4:
                etat->bas = val;
                break;
            default:
                break;
            }
        }

        // Détermination de la distance de Pacman par rapport au fantome
        int dPac = pow(tabPerso[0]->posX - tabPerso[idFantome]->posX, 2) + pow(tabPerso[0]->posY - tabPerso[idFantome]->posY, 2);
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

        // Détermination de la distance du fantome par rapport à l'autre fantome
        int dPacFan = pow(tabPerso[idFantome]->posX - tabPerso[idAutreFant]->posX, 2) + pow(tabPerso[idFantome]->posY - tabPerso[idAutreFant]->posY, 2);
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

        // Calcul de la direction où se trouve Pacman
        if (abs(tabPerso[idFantome]->posX - tabPerso[0]->posX) < abs(tabPerso[idFantome]->posY - tabPerso[0]->posY))
        {
            if (tabPerso[idFantome]->posX - tabPerso[0]->posX < 0)
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
            if (tabPerso[idFantome]->posY - tabPerso[0]->posY < 0)
            {
                etat->dir_pacman = S;
            }
            else
            {
                etat->dir_pacman = N;
            }
        }

        // Calcul de la direction où se trouve le fantôme
        if (abs(tabPerso[idFantome]->posX - tabPerso[idAutreFant]->posX) < abs(tabPerso[idFantome]->posY - tabPerso[idAutreFant]->posY))
        {
            if (tabPerso[idFantome]->posX - tabPerso[idAutreFant]->posX < 0)
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
            if (tabPerso[idFantome]->posY - tabPerso[idAutreFant]->posY < 0)
            {
                etat->dir_fantome = S;
            }
            else
            {
                etat->dir_fantome = N;
            }
        }
    }
    return etat;
}

int getMoveOpti(regles_t **regles, regles_t *etatPlateau, int **plateau, perso_t **tabPerso, int nbRegles, double s, int idFantome)
{
    int dir = 0;

    int nbPossibilite = 0;
    int *tabPoss = malloc(sizeof(int) * nbRegles);
    for (int i = 0; i < nbRegles; i++)
    {
        if (compareRegle(regles[i], etatPlateau) == 0)
        {
            if (movePossible(plateau, tabPerso[idFantome]->posX, tabPerso[idFantome]->posY, regles[i]->action))
            {
                tabPoss[nbPossibilite] = i;
                nbPossibilite++;
            }
        }
    }
    if (nbPossibilite != 0)
    {
        double poidsMax = 0;
        for (int k = 0; k < nbPossibilite; k++)
        {
            poidsMax += pow(regles[tabPoss[k]]->priorite, s);
        }

        int mouv = 0;
        if (poidsMax == 0)
        {
            for (int k = 0; k < nbPossibilite; k++)
            {
                poidsMax += pow(regles[tabPoss[k]]->priorite, s) + 1;
            }
            double nextMove = (double)rand() / (double)RAND_MAX;

            while (nextMove >= 0)
            {
                nextMove -= (pow(regles[tabPoss[mouv]]->priorite, s) + 1) / poidsMax;
                mouv++;
            }
            mouv--;
        }
        else
        {
            double nextMove = (double)rand() / (double)RAND_MAX;

            while (nextMove >= 0)
            {
                nextMove -= pow(regles[tabPoss[mouv]]->priorite, s) / poidsMax;
                mouv++;
            }
            mouv--;
        }
        dir = regles[tabPoss[mouv]]->action;
    }
    free(tabPoss);
    return dir;
}

int testParcoursProche(regles_t **tabRegle, int nbRegle, perso_t **tabPerso, int **plateau, int w, int h, double s)
{
    int nbIter = 0;
    int mort = 0;
    int distMin = -1;
    while (nbIter < 100 && mort != 1)
    {

        int dirPac = movePacmanIA(plateau, tabPerso[0]);
        movePersoInPlateau(plateau, &tabPerso[0]->posX, &tabPerso[0]->posY, tabPerso[0]->id, dirPac, &mort);
        int **heuri = heuristique(plateau, tabPerso[0]->posX, tabPerso[0]->posY, w, h);
        int dist = 0;
        for (int i = 1; i < 5; i++)
        {
            regles_t *etatPlat = calculEtat(plateau, tabPerso, w, i);
            int dir = getMoveOpti(tabRegle, etatPlat, plateau, tabPerso, nbRegle, s, i);

            movePersoInPlateau(plateau, &tabPerso[i]->posX, &tabPerso[i]->posY, tabPerso[i]->id, dir, &mort);
            dist += heuri[tabPerso[i]->posX][tabPerso[i]->posY] * 100 + nbIter;

            free(etatPlat);
        }
        dist = dist / 4;
        if (distMin == -1 || distMin > dist)
        {
            distMin = dist;
        }
        freeHeuri(heuri, w);
        nbIter++;
    }
    return distMin;
}

int testParcoursFinLevel(regles_t **tabRegle, int nbRegle, perso_t **tabPerso, int **plateau, int w, int h, double s)
{
    int nbIter = 0;
    int mort = 0;
    while (nbIter < 600 && mort != 1)
    {

        int dirPac = movePacmanIA(plateau, tabPerso[0]);
        movePersoInPlateau(plateau, &tabPerso[0]->posX, &tabPerso[0]->posY, tabPerso[0]->id, dirPac, &mort);
        for (int i = 1; i < 5; i++)
        {
            regles_t *etatPlat = calculEtat(plateau, tabPerso, w, i);
            int dir = getMoveOpti(tabRegle, etatPlat, plateau, tabPerso, nbRegle, s, i);
            movePersoInPlateau(plateau, &tabPerso[i]->posX, &tabPerso[i]->posY, tabPerso[i]->id, dir, &mort);

            free(etatPlat);
        }
        nbIter++;
    }
    return nbIter;
}

int parcours(regles_t **tabRegle, int nbRegle, int type, double s)
{

    int w, h;
    int **plateau = loadPlateau("./source/lvl/lvl3.txt", &w, &h);
    perso_t *Pac_man = initPac_man(plateau, w, h);
    perso_t *Blinky = initBlinky(plateau, w, h);
    perso_t *Clyde = initClyde(plateau, w, h);
    perso_t *Inky = initInky(plateau, w, h);
    perso_t *Pinky = initPinky(plateau, w, h);
    perso_t **tabPerso = malloc(sizeof(perso_t *) * 5);
    tabPerso[0] = Pac_man;
    tabPerso[1] = Blinky;
    tabPerso[2] = Clyde;
    tabPerso[3] = Inky;
    tabPerso[4] = Pinky;
    int dist = 0;

    if (type == 0)
    {
        dist = testParcoursProche(tabRegle, nbRegle, tabPerso, plateau, w, h, s);
    }
    else
    {
        dist = testParcoursFinLevel(tabRegle, nbRegle, tabPerso, plateau, w, h, s);
    }

    for (int i = 0; i < 5; i++)
    {
        free(tabPerso[i]);
    }
    free(tabPerso);
    freePlateau(plateau, w);

    return dist;
}

int treatment(void *parameters)
{
    param_t *p = (param_t *)parameters;
    int sortie = 0;
    int sommeCarr = 0;
    int val = 0;
    int variance = 0;
    for (int i = 0; i < 100; i++)
    {
        val = parcours(p->listeRegle, 16, p->type, S);
        sommeCarr+= pow(val,2);
        sortie += val;
    }
    sortie = sortie / 100;
    variance= sommeCarr/100 - pow(sortie,2);
    p->valSortie[p->id] = sortie+ sqrt(variance);
    return 0;
}

int compareRes(int *valOpti, int parcOrdre, int *ordreRegle, char *source, int type, int NBREGLE, int id, int *valSortieG)
{

    int numRegle = ordreRegle[parcOrdre] / 10;
    int numContrainte = ordreRegle[parcOrdre] % 10;
    int nbPoss = possibilite(numContrainte);
    int *listPos = createListePos(nbPoss, numContrainte);
    int *valSortie = malloc(sizeof(int) * nbPoss);

    thrd_t *tabThread = malloc(sizeof(thrd_t) * nbPoss);
    param_t **tabParam = malloc(sizeof(param_t *) * nbPoss);

    int valRetour = 10;

    // Création du tableau de paramètres
    for (int i = 0; i < nbPoss; i++)
    {
        param_t *param = malloc(sizeof(param_t));
        regles_t **regleParam = loadRegles(source, valOpti);
        if (numContrainte == 8 || numContrainte == 9)
        {
            modifRegle(regleParam[numRegle], numContrainte, i + 1);
        }
        else
        {
            modifRegle(regleParam[numRegle], numContrainte, i - 1);
        }

        valSortie[i] = 10001;
        param->type = type;
        param->id = i;
        param->listeRegle = regleParam;
        param->valSortie = valSortie;
        tabParam[i] = param;
    }
    // Creation des Thread
    for (int i = 0; i < nbPoss; i++)
    {
        thrd_create(&tabThread[i], treatment, tabParam[i]);
    }
    for (int i = 0; i < nbPoss; i++)
    {
        int error_code_of_thread = 0;
        thrd_join(tabThread[i], &error_code_of_thread);
    }
    int next = 0;
    int valmin = 10001;

    // Récuperation de de la valeur minimum calculé par les threads
    for (int i = 0; i < nbPoss; i++)
    {

        if (valSortie[i] < valmin)
        {
            valmin = valSortie[i];
            next = i;
        }
    }
    valSortieG[id] = valmin;
    if (*valOpti == -1 || valmin < *valOpti)
    {
        *valOpti = valmin;

        if (numContrainte == 8 || numContrainte == 9)
        {
            valRetour = next + 1;
        }
        else
        {
            valRetour = next - 1;
        }
    }
    printf("val : %d\n", valmin);
    printf("opti : %d\n", *valOpti);
    for (int i = 0; i < nbPoss; i++)
    {
        freeCerveau(tabParam[i]->listeRegle, NBREGLE);
        free(tabParam[i]);
        tabParam[i] = NULL;
    }
    free(tabParam);
    tabParam = NULL;
    free(valSortie);
    valSortie = NULL;

    free(listPos);
    listPos = NULL;

    return valRetour;
}
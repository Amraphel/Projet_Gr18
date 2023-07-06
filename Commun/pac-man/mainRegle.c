#include "calculRegle.h"
#ifndef REGLES
#define REGLES
#include "regles.h"
#endif

#define NBREGLE 16
#define S 4

int main()
{
    time_t t;
    time(&t);
    srand(t);
    char *source = "./source/regles/regle4.txt";
    char *dest = "./source/regles/regleTemp.txt";
    int valOpti = -1;
    int type = 1;
    // regles_t **regle = createMatRegles(NBREGLE);
    // initCerveau(regle, NBREGLE);
    // ecrireRegle(regle, source, NBREGLE, -1);
    // freeCerveau(regle, NBREGLE);
    // parcours(regle,NBREGLE, 1, S);
    int *ordreRegle = initRegle(NBREGLE, 10);
    int parcOrdre = 0;
    int compt = 0;
    int oldOpti = 0;
    for (int k = 0; k < 100000; k++)
    {

        if (parcOrdre >= (NBREGLE * 10))
        {
            shuffleRegle(NBREGLE, 10, ordreRegle);
            parcOrdre = 0;
        }
        // if (k == 500)
        // {
        //     type = 1;
        // }

        int numRegle = ordreRegle[parcOrdre] / 10;
        int numContrainte = ordreRegle[parcOrdre] % 10;
        parcOrdre++;

        int nbPoss = possibilite(numContrainte);
        int *listPos = createListePos(nbPoss, numContrainte);
        int *valSortie = malloc(sizeof(int) * nbPoss);
        regles_t **regle = loadRegles(source, &valOpti);
        int valRand = rand() % nbPoss;
        regles_t **regle2 = loadRegles(source, &valOpti);
        int *changeOpti = malloc(sizeof(int) * nbPoss);
        if (oldOpti != valOpti)
        {
            oldOpti = valOpti;
            compt = 0;
        }
        compt++;
        printf("compt %d\n", compt);
        if (compt > NBREGLE * 10)
        {
            for (int i = 0; i < nbPoss; i++)
            {
                if (numContrainte == 8 || numContrainte == 9)
                {
                    modifRegle(regle2[numRegle], numContrainte, (valRand + i) % nbPoss + 1);
                }
                else
                {
                    modifRegle(regle2[numRegle], numContrainte, (valRand + i) % nbPoss - 1);
                }
                ecrireRegle(regle2, dest, NBREGLE, valOpti);
                changeOpti[i] = compareRes(&valOpti, parcOrdre, ordreRegle, dest, type, NBREGLE, i, valSortie);
            }
            int bonneRegle = -1;
            for (int i = 0; i < nbPoss; i++)
            {
                if (valOpti == valSortie[i] && changeOpti[i] != 10)
                {
                    bonneRegle = i;
                }
            }

            if (bonneRegle != -1)
            {
                regle[numRegle] = regle2[numRegle];
                numRegle = ordreRegle[parcOrdre] / 10;
                numContrainte = ordreRegle[parcOrdre] % 10;
                modifRegle(regle[numRegle], numContrainte, changeOpti[bonneRegle]);
            }
            parcOrdre++;
        }
        else
        {
            changeOpti[0] = compareRes(&valOpti, parcOrdre, ordreRegle, source, type, NBREGLE, 0, valSortie);
            if (changeOpti[0] != 10)
            {
                modifRegle(regle[numRegle], numContrainte, changeOpti[0]);
            }
        }

        ecrireRegle(regle, source, NBREGLE, valOpti);
        free(valSortie);
        free(changeOpti);
        free(listPos);
        freeCerveau(regle, NBREGLE);
    }

    return 0;
}
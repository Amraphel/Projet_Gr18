#include "calculRegle.h"
#ifndef REGLES
#define REGLES
#include "regles.h"
#endif

#define NBREGLE 12
int treatment(void *parameters)
{
    param_t *p = (param_t *)parameters;
    p->valSortie[p->id] = parcours(p->listeRegle);
    return 0;
}

int main()
{
    time_t t;
    time(&t);
    srand(t);
    char *source = "./source/regles/regle.txt";
    char *dest = "./source/regles/regle2.txt";
    regles_t **regle = loadRegles(source);

    int numRegle = rand() % NBREGLE + 1;
    int numContrainte = rand() % 10;
    int nbPoss = possibilite(numContrainte);

    int *listPos = createListePos(nbPoss);
    int *valSortie = malloc(sizeof(int) * nbPoss);

    thrd_t *tabThread = malloc(sizeof(thrd_t) * nbPoss);
    param_t **tabParam = malloc(sizeof(param_t *) * nbPoss);

    for (int i = 0; i < nbPoss; i++)
    {
        param_t *param = malloc(sizeof(param_t));
        regles_t **regleParam = loadRegles(source);
        modifRegle(regleParam[numRegle], numContrainte, i - 1);

        valSortie[i] = 5001;
        param->id = i;
        param->listeRegle = regleParam;
        param->valSortie = valSortie;
        tabParam[i] = param;
    }
    for (int i = 0; i < nbPoss; i++)
    {
        thrd_create(&tabThread[i], treatment, tabParam[i]);
    }
    for (int i = 0; i < nbPoss; i++)
    {
        int error_code_of_thread = 0;
        thrd_join(tabThread[i], &error_code_of_thread);
    }

    for (int i = 0; i < nbPoss; i++)
    {
        printf("%d ", valSortie[i]);

        for (int j = 0; j < NBREGLE; j++)
        {
            free(tabParam[i]->listeRegle[j]);
            tabParam[i]->listeRegle[j] = NULL;
        }
        free(tabParam[i]->listeRegle);
        tabParam[i]->listeRegle = NULL;
        free(tabParam[i]);
    }
    printf("\n");

    free(tabParam);
    free(valSortie);
    valSortie = NULL;

    free(listPos);
    listPos=NULL;

    // int dist = parcours(regle);
    // printf("dist : %d\n", dist);
    return 0;
}
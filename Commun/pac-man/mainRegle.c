#include "calculRegle.h"
#ifndef REGLES
#define REGLES
#include "regles.h"
#endif

#define NBREGLE 16
#define S 6

int treatment(void *parameters)
{
    param_t *p = (param_t *)parameters;
    int sortie = 0;
    for (int i = 0; i < 10; i++)
    {
        sortie += parcours(p->listeRegle, p->type,S);
    }
    sortie = sortie / 10;
    p->valSortie[p->id] = sortie;
    return 0;
}

int main()
{
    time_t t;
    time(&t);
    srand(t);
    char *source = "./source/regles/regle3.txt";
    char *dest = "./source/regles/regle3.txt";
    int valOpti=-1;
    int type=0;
    // regles_t **regle = loadRegles(source, &valOpti);
    // parcours(regle,0);
    int * ordreRegle=initRegle(NBREGLE, 10);
    int parcOrdre=0;

    for (int k = 0; k < 1000; k++)
    {
        if(parcOrdre%(NBREGLE*10)==0){
            shuffleRegle(NBREGLE,10,ordreRegle);
            parcOrdre=0;
        }
        // if(k==600){
        //     type=1;
        //     valOpti=10000;        }
        regles_t **regle = loadRegles(source, &valOpti);

        int numRegle = ordreRegle[parcOrdre] / 10;
        int numContrainte = ordreRegle[parcOrdre] % 10;
        // fprintf(stderr, "numR : %d et numC : %d\n", numRegle, numContrainte);
        int nbPoss = possibilite(numContrainte);
        parcOrdre++;
        int *listPos = createListePos(nbPoss);
        int *valSortie = malloc(sizeof(int) * nbPoss);

        thrd_t *tabThread = malloc(sizeof(thrd_t) * nbPoss);
        param_t **tabParam = malloc(sizeof(param_t *) * nbPoss);

        int valRand= rand()%nbPoss;
        for (int i = 0; i < nbPoss; i++)
        {
            param_t *param = malloc(sizeof(param_t));
            regles_t **regleParam = loadRegles(source, &valOpti);
            if(numContrainte ==8){
                modifRegle(regleParam[numRegle], numContrainte, (valRand+i)%nbPoss + 1);
            }else{
                modifRegle(regleParam[numRegle], numContrainte, (valRand+i)%nbPoss - 1);
            }
            

            valSortie[i] = 10001;
            param->type=type;
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
        int next = 0;
        int valmin = 10001;

        for (int i = 0; i < nbPoss; i++)
        {
            
            if (valSortie[i] < valmin)
            {
                valmin = valSortie[i];
                next = i;
            }
        }
        if(valOpti==-1 || valmin<valOpti){
            valOpti=valmin;
            ecrireRegle(tabParam[next]->listeRegle, dest, NBREGLE, valOpti);
        } else{
            ecrireRegle(regle, dest, NBREGLE, valOpti);
        }
        printf("val : %d next : %d\n", valmin,next);
        printf("opti : %d\n", valOpti);
        for (int i = 0; i < nbPoss; i++)
        {
            freeCerveau(tabParam[i]->listeRegle, NBREGLE);
            free(tabParam[i]);
            tabParam[i] = NULL;
        }
        freeCerveau(regle, NBREGLE);


        free(tabParam);
        tabParam = NULL;
        free(valSortie);
        valSortie = NULL;

        free(listPos);
        listPos = NULL;
    }

    return 0;
}
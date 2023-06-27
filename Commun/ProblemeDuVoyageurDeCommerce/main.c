#include "affichage.h"

int main()
{
    int nb = 3;
    SDL_Window* window = initWindow(200,200,200,200);
    point_t *p = NULL;
    p = tabPointAleatoire(nb, window);
    free(p);
}
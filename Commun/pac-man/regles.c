// int ** createMatRegles(int width, int height)
// {
//     int **matRegles = malloc(sizeof(int *) * width);
//     for (int i = 0; i < width; i++)
//     {
//         int *ligne = malloc(sizeof(int) * height);
//         matRegles[i] = ligne;
//         for (int j = 0; j < height; j++)
//         {
//             matRegles[i][j] = 0;
//         }
//     }
//     return matRegles;
// }

// int **loadRegles(char *regles)
// {
//     int **matRegles = NULL;
//     FILE *file = fopen(regles, "r");
//     int* w, h;
//     if (file)
//     {
//         fscanf(file, "%d %d\n", w, h);

//         matRegles = createMatRegles(*w, *h);
//         for (int i = 0; i < *w; i++)
//         {
//             for (int j = 0; j < *h; j++)
//             {
//                 fscanf(file, "%d ", &matRegles[i][j]);
//             }
//             fscanf(file, "\n");
//         }
//         // printPlateau(plateau, *w, *h);
//     }
//     fclose(file);
//     return matRegles;
// }
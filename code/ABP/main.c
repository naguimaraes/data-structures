/* Ian && Nathan- Cartão UFRGS:
15.08.22
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "shared.h"
#include "ABP.h"


int main(int agrc, char *argv[])
{
    if (agrc != 3)
    {
        printf("Usage: <Programa>  <Calorias> <AlimentosIngeridos> <Arquivo de saida>\n");
        return 1;
    }

    Alimento test;
    FILE *file = fopen(argv[0], "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo de alimentos\n");
        return 1;
    }
    getAlimento(&test, file);
    printf("%s\n%d\n", test.name, test.caloriesPer100Grams);
    fclose(file);

    int ABP = 0, AVL = 0, RN = 0, Splay = 0;


    return 0;
}
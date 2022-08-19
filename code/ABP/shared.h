#ifndef SHARED_H_
#define SHARED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Alimento
{
    char *name;
    int caloriesPer100Grams;
}Alimento;

typedef struct Ingerido
{
    char *name;
    int quantityInGrams;
}Ingerido;

float caloriasIngeridas(Alimento Alimento, Ingerido ingerido)
{   
    return (Alimento.caloriesPer100Grams/100) * ingerido.quantityInGrams;
}

int getAlimento(Alimento *Alimento, FILE *file)
{
    if (Alimento == NULL||file == NULL)
    {
        return -1;
    }

    char *temp = (char *)malloc(sizeof(char) * 100);
    
    if(fgets(temp, 100, file) != NULL)
    {
        free(temp);
        return 1;        
    }

    Alimento->name = strtok(temp, ";");
    Alimento->caloriesPer100Grams = atoi(strtok(NULL, ";"));

    free(temp);
    return 0;
}

#endif
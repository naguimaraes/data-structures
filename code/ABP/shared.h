#ifndef SHARED_H_
#define SHARED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Alimento
{
    char name[100];
    int caloriesPer100Grams;
}Alimento;

typedef struct Ingerido
{
    char name[100];
    int quantityInGrams;
}Ingerido;

typedef struct Statistics
{
    char name[100];
    int numNodes;
    int height;
    int rotations;
    int comparasions;
} Statistics;

typedef struct Counter
{
    Statistics ABP;
    Statistics AVL;
    Statistics RN;
    Statistics Splay;
} Counter;

void outputStart(int argc, char *argv[], FILE **outputFile, FILE **day, FILE **food, Counter *counter, int *totalCals);

void outputEnd(FILE **outputFile, FILE **day, FILE **food, Counter counter, int totalCals);

float caloriasIngeridas(Alimento Alimento, Ingerido ingerido);

int getAlimento(Alimento *alimento, FILE *file);

int getIngerido(Ingerido *ingerido, FILE *file);

char *getOutputString(Alimento alimento, Ingerido ingerido);

int outputToFile(char *output, FILE *file);

char *printStatistics(Statistics stats);

int startOutputFile(FILE *file, char *argv[]);

int finishOutputFile(FILE *file, Counter counter, int totalCals);

Counter initCounter();

#endif
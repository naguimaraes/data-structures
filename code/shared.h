#ifndef SHARED_H_
#define SHARED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structs para as estatisticas de saida
typedef struct Statistics
{
    char name[100];
    int numNodes;
    int height;
    int rotations;
    int comparasions;
} Statistics;

// Structs para conter os contadores de todas as arvores
typedef struct Counter
{
    Statistics ABP;
    Statistics AVL;
    Statistics RN;
    Statistics Splay;
} Counter;

// Structs para conter os dados do programa para passagem mais rapida
typedef struct Outputs
{
    FILE *arg1Foods;
    FILE *arg2Day;
    FILE *arg3OutputFile;
    Counter counter;
    int totalCals;
} Outputs;	

// Structs para conter os dados do alimento
typedef struct Alimento
{
    char name[100];
    int caloriesPer100Grams;
}Alimento;

// Structs para conter os dados do alimento
typedef struct Ingerido
{
    char name[100];
    int quantityInGrams;
}Ingerido;

// Rotina que inicializa os elementos do programa
void outputStart(int argc, char *argv[], Outputs *output);

// Rotina que finaliza os elementos do programa
void outputEnd(Outputs *output);

// Rotina que retorna o alimento
float caloriasIngeridas(Alimento Alimento, Ingerido ingerido);

// Rotina que retorna o alimento como parametro
int getAlimento(Alimento *alimento, FILE *file);

// Rotina que retorna o alimento como parametro
int getIngerido(Ingerido *ingerido, FILE *file);

// Rotina que retorna uma string com os dados do alimento
char *getOutputString(Alimento alimento, Ingerido ingerido);

// Rotina que escreve uma string para o arquivo de saida
int outputToFile(char *output, FILE *file);

// Rotina que escreve no arquivo de saida os dados de estatisticas de uma arvore
char *printStatistics(Statistics stats);

// Rotina que inicia a escrever o arquivo de saida
int startOutputFile(FILE *file, char *argv[]);

// Rotina que finaliza de escrever o arquivo de saida
int finishOutputFile(FILE *file, Counter counter, int totalCals);

// Rotina que inicializa os contadores de todas as arvores
Counter initCounter();

#endif
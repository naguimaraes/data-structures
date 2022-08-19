#ifndef SHARED_H_
#define SHARED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structs para as estatisticas de saida
typedef struct Statistics
{
    char name[100]; // Nome da arvire
    int numNodes; // Numero de nos da arvore
    int height; // Altura da arvore
    int rotations; // Numero de rotacoes da arvore
    int comparasions; // Numero de comparacoes da arvore
} Statistics;

// Structs para conter os contadores de todas as arvores
typedef struct Counter
{
    Statistics ABP; // Contador para a arvore ABP
    Statistics AVL; // Contador para a arvore AVL
    Statistics RN; // Contador para a arvore RN
    Statistics Splay; // Contador para a arvore Splay
} Counter;

// Structs para conter os dados do programa para passagem mais rapida
typedef struct Outputs
{
    FILE *arg1Foods; // Arquivo com os alimentos
    FILE *arg2Day; // Arquivo com os dias
    FILE *arg3OutputFile; // Arquivo de saida
    Counter counter; // Contador de todas as arvores
    int totalCals; // Total de calorias ingeridas
} Outputs;	

// Structs para conter os dados do alimento
typedef struct Alimento
{
    char name[100]; // Nome do alimento
    int caloriesPer100Grams; // Calorias por 100 gramas
}Alimento;

// Structs para conter os dados do alimento
typedef struct Ingerido
{
    char name[100]; // Nome do alimento
    int quantityInGrams; // Quantidade em gramas
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
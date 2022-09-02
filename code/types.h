#ifndef types_H_
#define types_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs para as estatisticas de saida
typedef struct TreeStats
{
    char name[100];  // Nome da arvire
    int counters[4]; // 0 numNodes, 1 height, 2 rotations, 3 comparasions
} TreeStats;

// Returns a new tree stats struct with given name
TreeStats initCounter(char name[]);

// retorna o ponteiro para o contador especifico de algo
// 1 - Nodes | 2 - Height | 3 - Rotations | 4 - Comparasions
int *getCounterIntPointer(TreeStats *stats, int index);

// retorna int para o contador especifico de algo
// 1 - Nodes | 2 - Height | 3 - Rotations | 4 - Comparasions
int getCounterInt(TreeStats *stats, int index);

// Retorna o ponteiro para o nome da estatistica
char *getCounterName(TreeStats *stats);

// Atualiza o nome do contador
void setCounterName(TreeStats *stats, char name[]);

// Adicion int para o contador especifico de algo
// 1 - Nodes | 2 - Height | 3 - Rotations | 4 - Comparasions
void addCounterInt(TreeStats *stats, int index, int value);

//! Outputs

// Structs para conter os dados do programa para passagem mais rapida
typedef struct Outputs
{
    FILE *file[3];      // Arquivos 1 - InputFoods, 2 - InputDays, 3 - OutputFile
    TreeStats stats[4]; // Contador para as arvores 1 - ABP, 2 - AVL, 3 - RN, 4 - Splay
    int totalCals;      // Total de calorias ingeridas
} Outputs;

// Retorna o contador de uma arvore especifica 
//1 = ABP, 2 = AVL, 3 = RN, 4 = Splay
TreeStats *getTreeStats(Outputs *counters, int index);

// Retorna o ponteiro para o arquivo
// 1 - Foods | 2 - Days | 3 - OutputFile
FILE *getFilePointer(Outputs *output, int index);

// Adiciona o ponteiro para o arquivo
// 1 - Foods | 2 - Days | 3 - OutputFile
void setFilePointer(Outputs *output, int index, FILE *file);

// Adiciona a quantidade de calorias ao total de calorias ingeridas
void addCals(Outputs *output, float cals);

// Retorna o total de calorias ingeridas
int getCals(Outputs *output);

//! FOODS

// Structs para conter os dados do alimento
typedef struct Food
{
    char name[100]; // Nome do alimento
    int calories;   // Calorias por 100 gramas ou quantidade ingerida em gramas
} Food;

char *getFoodName(Food *food);

int getFoodCals(Food *food);

void setFoodName(Food *food, char name[]);

void setFoodCals(Food *food, int cals);

// Returns how many calories were ingested in a day
int calsIngested(Food food, Food ingested);

#endif // types_H_
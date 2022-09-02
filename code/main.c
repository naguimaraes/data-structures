/* Ian && Nathan- Cartão UFRGS: 00338368 && ??
15.08.22
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "files.h" // Functions to write the files
#include "types.h" // Structs and functions for structs
#include "trees.h" // Shared function between tress

//! Funções das arvores
#include "ABP.h" // Cria as funções para a arvore ABP
#include "AVL.h" // Cria as funções para a arvore AVL
#include "RN.h" // Cria as funções para a arvore RN
#include "Splay.h" // Cria as funções para a arvore Splay

int main(int argc, char *argv[])
{
    printf("Initializing program...\n");
    Outputs output = initOutput(argc, argv); // Cria a struct para o output
    printf("\nProgram initilization successful!\n"); // Printa mensagem de status

    TreeStats *statsABP = getTreeStats(&output, 1);                 // Cria a struct para o contador da arvore ABP
    TreeStats *statsAVL = getTreeStats(&output, 2);                 // Cria a struct para o contador da arvore AVL
    // TreeStats *statsRN = getTreeStats(&output, 3);               // Cria a struct para o contador da arvore RN
    // TreeStats *statsSplay = getTreeStats(&output, 4);            // Cria a struct para o contador da arvore Splay

    printf("\nBuilding trees...\n");
    ABP *ABPtree = createTree(); // Cria a arvore ABP
    AVL *AVLtree = createTree(); // Cria a arvore AVL
    // RN *RNtree = createTree(); // Cria a arvore RN
    // Splay *Splaytree = createTree(); // Cria a arvore Splay
    printf("\nTrees created!\n");

    Food food;
    printf("\nReading food file...\n");
    while (!getFoodFromFile(&food, getFilePointer(&output, 1)))
    {
        insertABP(&ABPtree, food, statsABP); // Insere o alimento na arvore ABP
        insertAVL(&AVLtree, food, statsAVL); // Insere o alimento na arvore AVL
        // insertRN(&RNtree, food, statsRN); // Insere o alimento na arvore RN
        // insertSplay(&Splaytree, food, statsSplay); // Insere o alimento na arvore Splay
    }
    printf("\nFood file read!\n");

    printf("\nReading ingested food file and comparing...\n");
    for (char ingested[100], *x = fgets(ingested, 100, getFilePointer(&output, 2)); x != NULL; x = fgets(ingested, 100, getFilePointer(&output, 2)))
    {
        if (strchr(ingested, ';') != NULL)
        {
            strtok(ingested, ";"); // Remove o ; do nome do alimento
            for (int i = 0; i < strlen(ingested); i++) ingested[i] = tolower(ingested[i]); // Converte o nome do alimento para minusculo
            ABP *nodeABP = searchTree(ABPtree, ingested, statsABP); // Busca o alimento na arvore ABP
            AVL *nodeAVL = searchTree(AVLtree, ingested, statsAVL); // Busca o alimento na arvore AVL
            // RN *nodeRN = searchTree(RNtree, ingested, statsRN); // Busca o alimento na arvore RN
            // Splay *nodeSplay = searchTree(Splaytree, ingested, statsSplay); // Busca o alimento na arvore Splay

            if (nodeABP != NULL && nodeAVL != NULL
                // && nodeRN != NULL 
                // && nodeSplay != NULL
            )
            {
                int cals = atoi(strtok(NULL, ";")); // Pega a quantidade de calorias por 100 gramas do alimento
                addCals(&output, calsIngested(getInfo(nodeABP), cals));

                char *outputString = getOutputString(getInfo(nodeABP), cals); // Pega a string para o output
                outputStringToFile(outputString, getFilePointer(&output, 3));  // Escreve a string no arquivo de output
                free(outputString);
            }
        }
    }
    printf("\nIngested food file read!\n");

    printf("\nUpdating tree stats...\n");
    updateTreeCounter(statsABP, ABPtree); // Atualiza as estatisticas do ABP
    updateTreeCounter(statsAVL, AVLtree); // Atualiza as estatisticas do AVL
    // updateTreeCounter(statsRN, RNtree); // Atualiza as estatisticas do RN
    // updateTreeCounter(statsSplay, Splaytree); // Atualiza as estatisticas do Splay

    printf("\nDeleting trees...\n");
    deletTree(&ABPtree); // Destroi a arvore ABP
    deletTree(&AVLtree); // Destroi a arvore AVL
    // RNtree = destroyTree(RNtree); // Destroi a arvore RN
    // Splaytree = destroyTree(Splaytree); // Destroi a arvore Splay

    printf("\nWriting output file...\n");
    deletOutput(&output); // Finaliza o output do arquivo de saida

    printf("\nProgram finished!\n");
    return 0;
}
/* Ian && Nathan- Cartão UFRGS: 00338368 && 00334437
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
#include "LSE.h" // Cria as funções para a lista simplesmente encadeada

int main(int argc, char *argv[])
{
    printf("Initializing program...\n");
    Outputs output = initOutput(argc, argv); // Cria a struct para o output
    printf("\nProgram initilization successful!\n"); // Printa mensagem de status

    TreeStats *statsABP = getTreeStats(&output, 1);                 // Cria a struct para o contador da arvore ABP
    TreeStats *statsAVL = getTreeStats(&output, 2);                 // Cria a struct para o contador da arvore AVL
    TreeStats *statsRN = getTreeStats(&output, 3);               // Cria a struct para o contador da arvore RN
    TreeStats *statsSplay = getTreeStats(&output, 4);            // Cria a struct para o contador da arvore Splay
    TreeStats *statsLSE = getTreeStats(&output, 5);              // Cria a struct para o contador da arvore LSE

    printf("\nBuilding trees...\n");
    ABP *ABPtree = createTree(); // Cria a arvore ABP
    AVL *AVLtree = createTree(); // Cria a arvore AVL
    RN *RNtree = createTree(); // Cria a arvore RN
    Splay *Splaytree = createTree(); // Cria a arvore Splay
    LSE *LSEtree = createList(); // Cria a lista LSE
    printf("\nTrees created!\n");

    Food food;
    printf("\nReading food file...\n");
    while (!getFoodFromFile(&food, getFilePointer(&output, 1)))
    {
        insertABP(&ABPtree, food, statsABP); // Insere o alimento na arvore ABP
        insertAVL(&AVLtree, food, statsAVL); // Insere o alimento na arvore AVL
        insertRN(&RNtree, food, statsRN); // Insere o alimento na arvore RN
        insertSplay(&Splaytree, food, statsSplay); // Insere o alimento na arvore Splay
        insertLSEEnd(&LSEtree, food, statsLSE); // Insere o alimento na lista LSE
    }
    printf("\nFood file read!\n");

    Food ingested; // Cria o alimento que será ingerido
    printf("\nReading ingested food file and comparing...\n");
    while (!getFoodFromFile(&ingested, getFilePointer(&output, 2)))
    {
        ABP *nodeABP = consulta(ABPtree, ingested, statsABP);           // Busca o alimento na arvore ABP
        AVL *nodeAVL = consulta(AVLtree, ingested, statsAVL);           // Busca o alimento na arvore AVL
        RN *nodeRN = consulta(RNtree, ingested, statsRN);               // Busca o alimento na arvore RN
        Splay *nodeSplay = searchSplay(&Splaytree, ingested, statsSplay); // Busca o alimento na arvore Splay
        LSE *nodeLSE = searchLSE(LSEtree, ingested, statsLSE);           // Busca o alimento na lista LSE

        if (nodeABP != NULL && nodeAVL != NULL && nodeRN != NULL && nodeSplay != NULL && nodeLSE != NULL)
        {
            Food temp = getInfo(nodeABP); // Pega o alimento da arvore ABP, como todos encontraram, todos os "alimentos" são iguais
            
            addCals(&output, calsIngested(temp, ingested)); // Adiciona os calorias do alimento ao total de calorias
            
            char *outputString = getOutputString(temp, ingested); // Pega a string para o output
            outputStringToFile(outputString, getFilePointer(&output, 3)); // Escreve a string no arquivo de output
            free(outputString); // Libera a string
        }
    }
    printf("\nIngested food file read!\n");

    printf("\nUpdating tree stats...\n");
    updateTreeCounter(statsABP, ABPtree); // Atualiza as estatisticas do ABP
    updateTreeCounter(statsAVL, AVLtree); // Atualiza as estatisticas do AVL
    updateTreeCounter(statsRN, RNtree); // Atualiza as estatisticas do RN
    updateTreeCounter(statsSplay, Splaytree); // Atualiza as estatisticas do Splay

    printf("\nDeleting trees...\n");
    deletTree(&ABPtree); // Destroi a arvore ABP
    deletTree(&AVLtree); // Destroi a arvore AVL
    deletTree(&RNtree); // Destroi a arvore RN
    deletTree(&Splaytree); // Destroi a arvore Splay
    deletList(&LSEtree); // Destroi a lista LSE

    printf("\nWriting output file...\n");
    deletOutput(&output); // Finaliza o output do arquivo de saida

    printf("\nProgram finished!\n");
    
    printf("Press Enter to Exit.");
    getc(stdin);
    return 0;
}

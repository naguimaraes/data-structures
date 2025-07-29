#include "ABP.h"

typedef struct ABP // Cria a estrutura de uma forma opaca para o programa main
{
    Typeinfo info;
    ABP *L;
    ABP *R;
} ABP;

int insertABP(ABP **root, Typeinfo info, TreeStats *stats)
{

    if (*root == NULL)
    {
        *root = (ABP *)malloc(sizeof(ABP)); // Aloca memoria para a raiz
        if (root == NULL)
        {
            return 0; // Retorna 0 para indicar que nao foi possivel alocar memoria
        }
        (*root)->info = info; // Insere o valor na raiz
        (*root)->L = NULL;    // Insere NULL na esquerda
        (*root)->R = NULL;    // Insere NULL na direita
        return 1;
    }
    else if (strcmp((*root)->info.name, info.name) > 0)
    {
        return insertABP(&((*root)->L), info, stats); // Insere na esquerda
    }
    else if (strcmp((*root)->info.name, info.name) < 0)
    {
        return insertABP(&((*root)->R), info, stats); // Insere na direita
    }
    else
    {
        return 0; // Retorna 0 para indicar que o valor ja existe na arvore
    }
}

int removeABP(ABP **root, Typeinfo info, TreeStats *stats)
{
    getCounterIntPointer(stats, 1); // Só pro compiler não encher o saco de variavel não usada

    if (*root == NULL)
    {
        return 0; // Retorna 0 para indicar que o valor nao existe na arvore
    }

    if (strcmp((*root)->info.name, info.name) > 0)
    {
        return removeABP(&((*root)->L), info, stats); // Remove na esquerda
    }
    else if (strcmp((*root)->info.name, info.name) < 0)
    {
        return removeABP(&((*root)->R), info, stats); // Remove na direita
    }
    else
    {
        if ((*root)->L == NULL && (*root)->R == NULL)
        {
            free(*root);  // Libera a memoria da raiz
            *root = NULL; // Atualiza a raiz para NULL
            return 1;     // Retorna 1 para indicar que o valor foi removido
        }
        else if ((*root)->L == NULL)
        {
            ABP *aux = *root;   // Cria um auxiliar para guardar a raiz
            *root = (*root)->R; // Atualiza a raiz para a direita
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else if ((*root)->R == NULL)
        {
            ABP *aux = *root;   // Cria um auxiliar para guardar a raiz
            *root = (*root)->L; // Atualiza a raiz para a esquerda
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else
        {
            ABP *aux = (*root)->L; // Cria um auxiliar para guardar a raiz
            while (aux->R != NULL)
            { // Enquanto o auxiliar nao tiver filho da direita
                aux = aux->R;
            }
            (*root)->info = aux->info;           // Atualiza a raiz para o valor do auxiliar
            removeABP(&((*root)->L), aux->info, stats); // Remove o valor do auxiliar
            return 1;                            // Retorna 1 para indicar que o valor foi removido
        }
    }
    return 0; // Retorna 0 para indicar que o valor nao existe na arvore
}
#include "trees.h"

typedef struct Tree
{
    Typeinfo info;
    struct Tree *L;
    struct Tree *R;
} Tree;

void *createTree(void)
{
    return NULL;
}

void *searchTree(void *inputTree, Typeinfo info, TreeStats *stats)
{
    Tree *root = (Tree *)inputTree;
    addCounterInt(stats, 4, 1);
    if (root == NULL)
    {
        return NULL; // Retorna NULL para indicar que o valor nao existe na arvore
    }

    if (!strcmp(root->info.name, info.name))
    {
        addCounterInt(stats, 4, 1);
        return root; // Retorna a raiz para indicar que o valor existe na arvore
    }

    addCounterInt(stats, 4, 1);
    return strcmp(root->info.name,info.name) > 0 ? searchTree(root->L, info, stats) : searchTree(root->R, info, stats); // Busca o valor na arvore
}

void printTree(Tree *root, int level)
{
    if (root != NULL)
    { // Se a raiz nao for NULL
        for (int i = 0; i < level; i++)
        {
            printf("---"); // Imprime o numero de --- equivalente ao nivel da arvore
        }
        printf("%s (%d cals)\n", root->info.name, root->info.calories); // Imprime o valor da raiz
    }
}

int displayTreeNum(Tree *root, int mode, int level)
{            // Versão de displayABP "privada" que é usada para indicar o nivel sem o usuario necessitar passar o nivel
    level++; // Incrementa o nivel
    if (root == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }

    if (mode == 1) // preFixadoE
    {
        printTree(root, level);
        displayTreeNum(root->L, mode, level);
        displayTreeNum(root->R, mode, level);
    }
    else if (mode == 2) // preFixadoD
    {
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
    }
    else if (mode == 3) // posFixadoE
    {
        displayTreeNum(root->L, mode, level);
        displayTreeNum(root->R, mode, level);
        printTree(root, level);
    }
    else if (mode == 4) // posFixadoD
    {
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
        printTree(root, level);
    }
    else if (mode == 5) // CentralE
    {
        displayTreeNum(root->L, mode, level);
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
    }
    else if (mode == 6) // CentralD
    {
        displayTreeNum(root->R, mode, level);
        printTree(root, level);
        displayTreeNum(root->L, mode, level);
    }
    else if (mode == 6) // emFixadoD
    {
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
    }
    else
    {
        printf("Modo de impressão inválido\n"); // Imprime mensagem de erro
        return 0;                               // Retorna 0 para indicar que não foi possivel impirmir a arvore
    }
    return 1; // Retorna 1 para indicar que foi possivel imprimir todos os valores da arvore
}

int displayTree(void *inputTree, int mode)
{                  // Função para imprimir a arvore "publica" para a main
    int level = 0; // Nivel da arvore
    Tree *root = (Tree *)inputTree;
    if (root == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }

    if (mode == 1) // preFixadoE
    {
        printTree(root, level);
        displayTreeNum(root->L, mode, level);
        displayTreeNum(root->R, mode, level);
    }
    else if (mode == 2) // preFixadoD
    {
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
    }
    else if (mode == 3) // posFixadoE
    {
        displayTreeNum(root->L, mode, level);
        displayTreeNum(root->R, mode, level);
        printTree(root, level);
    }
    else if (mode == 4) // posFixadoD
    {
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
        printTree(root, level);
    }
    else if (mode == 5) // CentralE
    {
        displayTreeNum(root->L, mode, level);
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
    }
    else if (mode == 6) // CentralD
    {
        displayTreeNum(root->R, mode, level);
        printTree(root, level);
        displayTreeNum(root->L, mode, level);
    }
    else if (mode == 6) // emFixadoD
    {
        printTree(root, level);
        displayTreeNum(root->R, mode, level);
        displayTreeNum(root->L, mode, level);
    }
    else
    {
        printf("Modo de impressão inválido\n"); // Imprime mensagem de erro
        return 0;                               // Retorna 0 para indicar que não foi possivel imprimir a arvore
    }
    return 1; // Retorna 1 para indicar que foi possivel imprimir todos os valores da arvore
}

void deletTree(void *inputTree)
{
    Tree **root = (Tree **)inputTree; // Converte o ponteiro para arvore
    
    if (*root == NULL)
    {
        return; // Retorna a arvore para indicar que nao existe nenhuma arvore para destruir
    }

    deletTree(&((*root)->L)); // Destroi a arvore da esquerda
    deletTree(&((*root)->R)); // Destroi a arvore da direita
    free(*root);                     // Libera a memoria da raiz
    *root = NULL;                    // Seta a raiz para NULL
}

Typeinfo getInfo(void *inputNode)
{
    Tree *node = (Tree *)inputNode; // Converte o ponteiro para arvore
    return node->info;
}

int numberNodes(void *inputTree)
{
    if (inputTree == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }
    Tree *root = (Tree *)inputTree;                         // Converte o ponteiro para arvore
    return 1 + numberNodes(root->L) + numberNodes(root->R); // Retorna o numero de nos da arvore
}

int heightTree(void *inputTree)
{
    if (inputTree == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }

    Tree *root = (Tree *)inputTree;             // Converte o ponteiro para arvore
    int left = heightTree(root->L);             // Calcula a altura da arvore da esquerda
    int right = heightTree(root->R);            // Calcula a altura da arvore da direita
    return 1 + ((left > right) ? left : right); // Retorna a altura da arvore
}

void updateTreeCounter(TreeStats *counter, void *tree)
{
    addCounterInt(counter, 1, numberNodes(tree)); // Adiciona o numero de nos da arvore
    addCounterInt(counter, 2, heightTree(tree));  // Adiciona a altura da arvore
}

Tree *_consulta(Tree *root, char *key, int *comp)
{
    while (root != NULL)
    {
        (*comp)++;
        if (!strcmp(root->info.name, key))
        {
            (*comp)++;
            return root;
        }
        else
        {
            (*comp)++;
            if (strcmp(root->info.name, key) > 0)
                root = root->L;
            else
                root = root->R;
        }
    }
    return NULL;
}

void *consulta(void *inputTree, Typeinfo info, TreeStats *stats)
{
    Tree *root = (Tree *)inputTree; // Converte o ponteiro para arvore
    if (root == NULL)
    {
        return NULL; // Retorna NULL para indicar que nao existe nenhum valor na arvore
    }
    root = _consulta(root, info.name, getCounterIntPointer(stats, 4)); // Chama a função recursiva
    return root;
}
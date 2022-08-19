#include "ABP.h"

typedef struct ABP // Cria a estrutura de uma forma opaca para o programa main
{
    Typeinfo info;
    ABP *L;
    ABP *R;
} ABP;

Tree *createABP(void)
{
    return NULL; // Retorna NULL para indicar que a arvore esta vazia
}

int insertABP(Tree **raiz, Typeinfo info)
{
    if (*raiz == NULL)
    {
        *raiz = (Tree *)malloc(sizeof(Tree)); // Aloca memoria para a raiz
        if (raiz == NULL)
        {
            return 0; // Retorna 0 para indicar que nao foi possivel alocar memoria
        }
        (*raiz)->info = info; // Insere o valor na raiz
        (*raiz)->L = NULL;    // Insere NULL na esquerda
        (*raiz)->R = NULL;    // Insere NULL na direita
        return 1;
    }
    else if (strcmp((*raiz)->info.name, info.name) > 0)
    {
        return insertABP(&((*raiz)->L), info); // Insere na esquerda
    }
    else if (strcmp((*raiz)->info.name, info.name) < 0)
    {
        return insertABP(&((*raiz)->R), info); // Insere na direita
    }
    else
    {
        return 0; // Retorna 0 para indicar que o valor ja existe na arvore
    }
}

int removeABP(Tree **raiz, Typeinfo info)
{
    if (*raiz == NULL)
    {
        return 0; // Retorna 0 para indicar que o valor nao existe na arvore
    }

    if (strcmp((*raiz)->info.name, info.name) > 0)
    {
        return removeABP(&((*raiz)->L), info); // Remove na esquerda
    }
    else if (strcmp((*raiz)->info.name, info.name) < 0)
    {
        return removeABP(&((*raiz)->R), info); // Remove na direita
    }
    else
    {
        if ((*raiz)->L == NULL && (*raiz)->R == NULL)
        {
            free(*raiz);  // Libera a memoria da raiz
            *raiz = NULL; // Atualiza a raiz para NULL
            return 1;     // Retorna 1 para indicar que o valor foi removido
        }
        else if ((*raiz)->L == NULL)
        {
            Tree *aux = *raiz;   // Cria um auxiliar para guardar a raiz
            *raiz = (*raiz)->R; // Atualiza a raiz para a direita
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else if ((*raiz)->R == NULL)
        {
            Tree *aux = *raiz;   // Cria um auxiliar para guardar a raiz
            *raiz = (*raiz)->L; // Atualiza a raiz para a esquerda
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else
        {
            Tree *aux = (*raiz)->L; // Cria um auxiliar para guardar a raiz
            while (aux->R != NULL)
            { // Enquanto o auxiliar nao tiver filho da direita
                aux = aux->R;
            }
            (*raiz)->info = aux->info;           // Atualiza a raiz para o valor do auxiliar
            removeABP(&((*raiz)->L), aux->info); // Remove o valor do auxiliar
            return 1;                            // Retorna 1 para indicar que o valor foi removido
        }
    }
    return 0; // Retorna 0 para indicar que o valor nao existe na arvore
}

Tree *searchABP(Tree *raiz, Typeinfo info, int *comp)
{
    if (raiz == NULL)
    {
        comp++;
        return NULL; // Retorna NULL para indicar que o valor nao existe na arvore
    }

    if (!strcmp(raiz->info.name, info.name))
    {
        comp++;
        return raiz; // Retorna a raiz para indicar que o valor existe na arvore
    }

    if (strcmp(raiz->info.name, info.name) > 0)
    {
        comp++;
        return searchABP(raiz->L, info, comp); // Busca na esquerda
    }
    else if (strcmp(raiz->info.name, info.name) < 0)
    {
        comp++;
        return searchABP(raiz->R, info, comp); // Busca na direita
    }
    else
    {
        return NULL; // Retorna NULL para indicar que o valor nao existe na arvore
    }
}

int destroiABP(Tree **raiz)
{
    if (*raiz != NULL)
    {
        destroiABP(&((*raiz)->L)); // Destroi a esquerda
        destroiABP(&((*raiz)->R)); // Destroi a direita
        free(*raiz);               // Libera a memoria da raiz
        *raiz = NULL;              // Atualiza a raiz para NULL
        return 1;                  // Retorna 1 para indicar que a arvore foi destruida
    }
    return 0;
}

void printABP(Tree *raiz, int level)
{
    if (raiz != NULL)
    { // Se a raiz nao for NULL
        for (int i = 0; i < level; i++)
        {
            printf("---"); // Imprime o numero de --- equivalente ao nivel da arvore
        }
        printf("%s\n", raiz->info.name); // Imprime o valor da raiz
    }
}

int displayABPNum(Tree *raiz, int mode, int level)
{            // Versão de displayABP "privada" que é usada para indicar o nivel sem o usuario necessitar passar o nivel
    level++; // Incrementa o nivel
    if (raiz == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }

    if (mode == 1) // preFixadoE
    {
        printABP(raiz, level);
        displayABPNum(raiz->L, mode, level);
        displayABPNum(raiz->R, mode, level);
    }
    else if (mode == 2) // preFixadoD
    {
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
    }
    else if (mode == 3) // posFixadoE
    {
        displayABPNum(raiz->L, mode, level);
        displayABPNum(raiz->R, mode, level);
        printABP(raiz, level);
    }
    else if (mode == 4) // posFixadoD
    {
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
        printABP(raiz, level);
    }
    else if (mode == 5) // CentralE
    {
        displayABPNum(raiz->L, mode, level);
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
    }
    else if (mode == 6) // CentralD
    {
        displayABPNum(raiz->R, mode, level);
        printABP(raiz, level);
        displayABPNum(raiz->L, mode, level);
    }
    else if (mode == 6) // emFixadoD
    {
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
    }
    else
    {
        printf("Modo de impressão inválido\n"); // Imprime mensagem de erro
        return 0;                               // Retorna 0 para indicar que não foi possivel impirmir a arvore
    }
    return 1; // Retorna 1 para indicar que foi possivel imprimir todos os valores da arvore
}

int displayABP(Tree *raiz, int mode)
{                  // Função para imprimir a arvore "publica" para a main
    int level = 0; // Nivel da arvore
    if (raiz == NULL)
    {
        return 0; // Retorna 0 para indicar que nao existe nenhum valor na arvore
    }

    if (mode == 1) // preFixadoE
    {
        printABP(raiz, level);
        displayABPNum(raiz->L, mode, level);
        displayABPNum(raiz->R, mode, level);
    }
    else if (mode == 2) // preFixadoD
    {
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
    }
    else if (mode == 3) // posFixadoE
    {
        displayABPNum(raiz->L, mode, level);
        displayABPNum(raiz->R, mode, level);
        printABP(raiz, level);
    }
    else if (mode == 4) // posFixadoD
    {
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
        printABP(raiz, level);
    }
    else if (mode == 5) // CentralE
    {
        displayABPNum(raiz->L, mode, level);
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
    }
    else if (mode == 6) // CentralD
    {
        displayABPNum(raiz->R, mode, level);
        printABP(raiz, level);
        displayABPNum(raiz->L, mode, level);
    }
    else if (mode == 6) // emFixadoD
    {
        printABP(raiz, level);
        displayABPNum(raiz->R, mode, level);
        displayABPNum(raiz->L, mode, level);
    }
    else
    {
        printf("Modo de impressão inválido\n"); // Imprime mensagem de erro
        return 0;                               // Retorna 0 para indicar que não foi possivel imprimir a arvore
    }
    return 1; // Retorna 1 para indicar que foi possivel imprimir todos os valores da arvore
}

// Tree *consulta(Tree *root, char *key, int *comp)
// {
//     while (root != NULL)
//     {
//         *comp++;
//         if (!strcmp(root->info.name, key))
//         {
//             *comp++;
//             return root;
//         }
//         else
//         {
//             *comp++;
//             if (strcmp(root->info.name, key) > 0)
//                 root = root->L;
//             else
//                 root = root->R;
//         }
//     }
//     return NULL;
// }
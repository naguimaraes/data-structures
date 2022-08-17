#include "ABP.h"

typedef struct ABP // Cria a estrutura de uma forma opaca para o programa main
{
    int info;
    ABP *L;
    ABP *R;
} ABP;

ABP *createABP(void)
{
    return NULL; // Retorna NULL para indicar que a arvore esta vazia
}

int insertABP(ABP **raiz, int info)
{
    if (*raiz == NULL)
    {
        *raiz = (ABP *)malloc(sizeof(ABP)); // Aloca memoria para a raiz
        if (raiz == NULL)
        {
            return 0; // Retorna 0 para indicar que nao foi possivel alocar memoria
        }
        (*raiz)->info = info; // Insere o valor na raiz
        (*raiz)->L = NULL;    // Insere NULL na esquerda
        (*raiz)->R = NULL;    // Insere NULL na direita
        return 1;
    }
    else if (info < (*raiz)->info)
    {
        return insertABP(&((*raiz)->L), info); // Insere na esquerda
    }
    else if (info > (*raiz)->info)
    {
        return insertABP(&((*raiz)->R), info); // Insere na direita
    }
    else
    {
        return 0; // Retorna 0 para indicar que o valor ja existe na arvore
    }
}

int removeABP(ABP **raiz, int info)
{
    if (*raiz == NULL)
    {
        return 0; // Retorna 0 para indicar que o valor nao existe na arvore
    }

    if (info < (*raiz)->info)
    {
        return removeABP(&((*raiz)->L), info); // Remove na esquerda
    }
    else if (info > (*raiz)->info)
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
            ABP *aux = *raiz;   // Cria um auxiliar para guardar a raiz
            *raiz = (*raiz)->R; // Atualiza a raiz para a direita
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else if ((*raiz)->R == NULL)
        {
            ABP *aux = *raiz;   // Cria um auxiliar para guardar a raiz
            *raiz = (*raiz)->L; // Atualiza a raiz para a esquerda
            free(aux);          // Libera a memoria da auxiliar
            return 1;           // Retorna 1 para indicar que o valor foi removido
        }
        else
        {
            ABP *aux = (*raiz)->L; // Cria um auxiliar para guardar a raiz
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

ABP *searchABP(ABP *raiz, int info)
{
    if (raiz == NULL)
    {
        return NULL; // Retorna NULL para indicar que o valor nao existe na arvore
    }

    if (info == raiz->info)
    {
        return raiz; // Retorna a raiz para indicar que o valor existe na arvore
    }

    if (info < raiz->info)
    {
        return searchABP(raiz->L, info); // Busca na esquerda
    }
    else if (info > raiz->info)
    {
        return searchABP(raiz->R, info); // Busca na direita
    }
    else
    {
        return NULL; // Retorna NULL para indicar que o valor nao existe na arvore
    }
}

int destroiABP(ABP **raiz)
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

void printABP(ABP *raiz, int level)
{
    if (raiz != NULL)
    { // Se a raiz nao for NULL
        for (int i = 0; i < level; i++)
        {
            printf("---"); // Imprime o numero de --- equivalente ao nivel da arvore
        }
        printf("%d\n", raiz->info); // Imprime o valor da raiz
    }
}

int displayABPNum(ABP *raiz, int mode, int level)
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

int displayABP(ABP *raiz, int mode)
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

int compareABP(ABP *raiz1, ABP *raiz2)
{
    if (raiz1 == NULL && raiz2 == NULL)
    {             // Se as duas arvores forem NULL
        return 1; // Retorna 1 para indicar que as duas arvores sao iguais
    }
    else if (raiz1 == NULL || raiz2 == NULL)
    {             // Se uma das arvores for NULL
        return 0; // Retorna 0 para indicar que as duas arvores sao diferentes
    }
    else if (raiz1->info == raiz2->info)
    {                                                                            // Se os valores das raizes forem iguais
        return compareABP(raiz1->L, raiz2->L) && compareABP(raiz1->R, raiz2->R); // Retorna 1 se as subarvores forem iguais
    }
    else
    {             // Se os valores das raizes forem diferentes
        return 0; // Retorna 0 para indicar que as duas arvores sao diferentes
    }
}

int mirrorABP(ABP *raiz, ABP **raiz2)
{
    if (raiz == NULL)
    {                      // Se a arvore for NULL
        destroiABP(raiz2); // Destroi a arvore
        return 1;          // Retorna 1 para indicar que a arvore foi copiada com sucesso
    }
    else
    {                                        // Se a arvore nao for NULL
        destroiABP(raiz2);                   // Destroi a arvore
        *raiz2 = (ABP *)malloc(sizeof(ABP)); // Aloca memoria para a arvore
        (*raiz2)->info = raiz->info;         // Copia o valor da raiz
        (*raiz2)->L = NULL;                  // Inicializa a subarvore esquerda com NULL
        (*raiz2)->R = NULL;                  // Inicializa a subarvore direita com NULL
        mirrorABP(raiz->L, &((*raiz2)->R));  // Copia a subarvore da esquerda
        mirrorABP(raiz->R, &((*raiz2)->L));  // Copia a subarvore da direita
        return 1;                            // Retorna 1 para indicar que a arvore foi copiada com sucesso
    }
}

int isABP(ABP *raiz)
{ // Função para verificar se a arvore é uma arvore binaria de pesquisa
    if (raiz == NULL)
    {             // Se a arvore for NULL
        return 1; // Retorna 1 para indicar que a arvore é uma arvore binaria de pesquisa
    }
    else if (raiz->L == NULL && raiz->R == NULL)
    {             // Se a arvore for uma folha
        return 1; // Retorna 1 para indicar que a arvore é uma arvore binaria de pesquisa
    }
    else if (raiz->L == NULL)
    { // Se a arvore for uma folha
        if (raiz->R->info > raiz->info)
        {                          // Se a raiz for maior que a subarvore da direita
            return isABP(raiz->R); // Retorna 1 se a subarvore da esquerda for uma arvore binaria de pesquisa
        }
        else
        {
            return 0; // Retorna 0 para indicar que a arvore nao é uma arvore binaria de pesquisa
        }
    }
    else if (raiz->R == NULL)
    {
        if (raiz->L->info < raiz->info)
        {                          // Se a raiz for maior que a subarvore da direita
            return isABP(raiz->L); // Retorna 1 se a subarvore da esquerda for uma arvore binaria de pesquisa
        }
        else
        {
            return 0; // Retorna 0 para indicar que a arvore nao é uma arvore binaria de pesquisa
        }
    }
    else if (raiz->L->info < raiz->info && raiz->R->info > raiz->info)
    {                                            // Se a arvore for uma arvore binaria de pesquisa
        return isABP(raiz->L) && isABP(raiz->R); // Retorna 1 se as subarvores forem uma arvore binaria de pesquisa
    }
    else
    {
        return 0; // Retorna 0 para indicar que a arvore não é uma arvore binaria de pesquisa
    }
}

int insertMirrorABP(ABP **raiz, int info)
{ // Função para inserir um valor na arvore binaria de pesquisa espelhada
    if (*raiz == NULL)
    {                                       // Se a arvore for NULL
        *raiz = (ABP *)malloc(sizeof(ABP)); // Aloca memoria para a arvore
        (*raiz)->info = info;               // Insere o valor na raiz
        (*raiz)->L = NULL;                  // Insere NULL na subarvore da esquerda
        (*raiz)->R = NULL;                  // Insere NULL na subarvore da direita
        return 1;                           // Retorna 1 para indicar que a arvore foi inserida com sucesso
    }
    else if (info < (*raiz)->info)
    {
        return insertABP(&((*raiz)->R), info); // Insere na subarvore da direita
    }
    else if (info > (*raiz)->info)
    {
        return insertABP(&((*raiz)->L), info); // Insere na subarvore da esquerda
    }
    else
    {
        return 0; // Retorna 0 para indicar que a arvore não foi inserida
    }
}
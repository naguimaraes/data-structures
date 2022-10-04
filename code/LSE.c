/* Ian Kersz - Cartão UFRGS: 00338368
Implementação das funções utilizadas no trabalho para a LSE.
*/

#include "LSE.h"

struct LSE
{                // estrutura do nó da lista
    Typeinfo info;     // numero do nó
    LSE *prox; // ponteiro para o nó seguinte
};

LSE *createList()
{
    return NULL; // retorna NULL para indicar que a lista está vazia
}

void deletList(LSE **ptLista)
{
    LSE *aux;              // Criamos um ponteiro auxiliar para percorrer a lista
    while (*ptLista != NULL) // Enquanto a lista não estiver vazia, percorremos a lista
    {
        aux = *ptLista;              // O ponteiro auxiliar aponta para o item atual da lista
        *ptLista = (*ptLista)->prox; // O ponteiro da lista aponta para o próximo item da lista
        free(aux);                   // Liberamos a memória do item atual da lista
    }
    *ptLista = NULL; // Retorna o ponteiro para NULL
}

void insertLSEStart(LSE **ptLista, Typeinfo info, TreeStats *stats)
{
    LSE *novo = (LSE *)malloc(sizeof(LSE)); // aloca memória para o nó
    memmove(&novo->info, &info, sizeof(Typeinfo));    // copia o valor para o nó
    novo->prox = *ptLista;                        // atribui o ponteiro da lista ao ponteiro prox do nó
    *ptLista = novo;                              // atribui o ponteiro novo ao ponteiro da lista
    addCounterInt(stats, 1, 1);
}

void insertLSEEnd(LSE **ptLista, Typeinfo info, TreeStats *stats)
{
    LSE *novo = (LSE *)malloc(sizeof(LSE)); // aloca memória para o nó
    memmove(&novo->info, &info, sizeof(Typeinfo)); // copia o valor para o nó
    novo->prox = NULL;                            // atribui NULL ao ponteiro prox do nó
    addCounterInt(stats, 1, 1);

    if (*ptLista == NULL) // se a lista estiver vazia, o nó é o primeiro da lista
    {
        *ptLista = novo; // atribui o ponteiro novo ao ponteiro da lista
    }
    else
    {
        LSE *aux = *ptLista; // cria um ponteiro auxiliar para percorrer a lista
        while (aux->prox != NULL) // percorre a lista até o último nó
        {
            aux = aux->prox; // ponteiro para o nó seguinte
        }
        aux->prox = novo; // atribui o ponteiro novo ao ponteiro prox do último nó
    }
}

void *searchLSE(LSE *ptLista, Typeinfo info, TreeStats *stats)
{
    while (ptLista != NULL) // percorre a lista até o final
    {
        addCounterInt(stats, 4, 1);
        if (strcmp(ptLista->info.name, info.name) == 0) // se o valor do nó for igual ao valor buscado, retorna o nó
        {
            return ptLista;
        }
        ptLista = ptLista->prox; // ponteiro para o nó seguinte
    }
    return NULL; // se o valor não for encontrado, retorna NULL
}
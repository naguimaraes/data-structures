#pragma once

/*
Interface da Lista Simples Encadeada em C e suas funções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct LSE LSE; // tipo do nó da lista

typedef struct Food Typeinfo;

LSE *createList(); // cria a lista

void deletList(LSE **ptLista); // destroi a lista

void insertLSEStart(LSE **ptLista, Typeinfo info, TreeStats *stats); // insere o valor na lista

void insertLSEEnd(LSE **ptLista, Typeinfo info, TreeStats *stats); // insere o valor no final da lista

void *searchLSE(LSE *ptLista, Typeinfo info, TreeStats *stats); // busca o valor na lista

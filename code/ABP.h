#ifndef ABP_H_
#define ABP_H_

#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

typedef struct ABP ABP;

typedef ABP Tree;

typedef Alimento Typeinfo;

Tree *createABP(void);

int insertABP(Tree **raiz, Typeinfo info);

int removeABP(Tree **raiz, Typeinfo info);

Tree *searchABP(Tree *raiz, Typeinfo info, int *comp);

int destroiABP(Tree **raiz);

int displayABP(Tree *raiz, int mode);

Tree *consulta(Tree *root, char *key, int *comp);

#endif
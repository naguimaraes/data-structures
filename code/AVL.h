#ifndef AVL_H_
#define AVL_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "trees.h"

typedef Food Typeinfo;

typedef struct AVL AVL;

int insertAVL(AVL **root, Typeinfo info, TreeStats *stats);

int removeAVL(AVL **root, Typeinfo info, TreeStats *stats);

#endif // AVL_H_
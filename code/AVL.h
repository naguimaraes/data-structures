#ifndef AVL_H_
#define AVL_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "trees.h"

typedef struct AVL AVL;
typedef Food Typeinfo;

int insertAVL(AVL **root, Typeinfo info, TreeStats *stats);

#endif // AVL_H_
#ifndef ABP_H_
#define ABP_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "trees.h"

typedef struct ABP ABP;
typedef struct Food Typeinfo;

int insertABP(ABP **root, Typeinfo info, TreeStats *stats);

int removeABP(ABP **root, Typeinfo info, TreeStats *stats);

#endif
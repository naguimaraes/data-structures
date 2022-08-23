#ifndef SPLAY_H_
#define SPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "trees.h"

typedef struct Splay Splay;
typedef struct Food Typeinfo;

int insertSplay(Splay **root, Typeinfo *info, TreeStats *stats);

#endif // SPLAY_H_
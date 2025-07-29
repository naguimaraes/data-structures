#ifndef RN_H_
#define RN_H_

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "trees.h"

typedef struct RN RN;
typedef struct Food Typeinfo;

int insertRN(RN **root, Typeinfo info, TreeStats *stats);

#endif // RN_H_
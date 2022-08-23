#ifndef TREES_H_
#define TREES_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "types.h"

typedef struct Food Typeinfo;

// All the common functions for the trees

// Returns NULL to create a tree pointer
void *createTree(void);

// Returns the node of the tree with the right info, NULL if not found
void *searchTree(void *inputTree, Typeinfo info, TreeStats *stats);

// Displays the tree in the terminal, input int determines mode, output int determines if the function was successful
// 1 - preFixadoE | 2 - preFixadoD | 3 - posFixadoE | 4 - posFixadoD
// 5 - CentralE |  6 - CentralD | 7 - emFixadoD
int displayTree(void *inputTree, int mode);

// Destroys the tree completely
void deletTree(void *inputTree);

Typeinfo getInfo(void *root);

int numberNodes(void *inputTree);

int heightTree(void *inputTree);

void updateTreeCounter(TreeStats *counter, void *tree);

void *consulta(void *inputTree, Typeinfo info, TreeStats *stats);

#endif
#include "RN.h"

typedef struct RN
{
    Typeinfo info;
    struct RN *L;
    struct RN *R;
    struct RN *P;
    int red;
} RN;

void sRotateRRN(RN **root, RN *node)
{
    RN *parent = node->P;
    RN *grandparent = NULL;
    RN *right = node->R;

    if (parent->P != NULL)
    {
        grandparent = parent->P;
        if (grandparent->R == parent)
        {
            grandparent->R = node;
        }
        else
        {
            grandparent->L = node;
        }
    }
    else
    {
        *root = node;
    }

    node->P = grandparent;
    node->R = parent;
    if (right != NULL)
        right->P = parent;

    parent->P = node;
    parent->L = right;
}

void sRotateLRN(RN **root, RN *node)
{
    RN *parent = node->P;
    RN *grandparent = NULL;
    RN *left = node->L;
    if (parent->P != NULL)
    {
        grandparent = parent->P;
        if (grandparent->R == parent)
        {
            grandparent->R = node; 
        }
        else
        {
            grandparent->L = node; 
        }
    }
    else
    {
        *root = node;
    }

    parent->P = node;
    parent->R = left;
    if (left != NULL)
        left->P = parent;

    node->P = grandparent;
    node->L = parent;
}

void VerifyRN(RN **root, RN *node, TreeStats *stats)
{
    if (node != NULL && node->P != NULL && node->P->P != NULL)
    {
        RN *parent = node->P;
        RN *grandparent = node->P->P;

        if (node->P->red == 1 && node->red == 1)
        {
            if (grandparent->R != parent)
            {
                if (grandparent->R != NULL && grandparent->R->red == 1)
                {
                    parent->red = 0;
                    grandparent->R->red = 0;
                    if (grandparent->P != NULL)
                        grandparent->red = 1;
                }
                else
                {
                    if (parent->R != node)
                    {
                        node->P->red = 0;
                        node->P->P->red = 1;
                        sRotateRRN(root, node->P);
                        addCounterInt(stats, 3, 1);
                    }
                    else
                    {
                        node->red = 0;
                        node->P->P->red = 1;
                        sRotateLRN(root, node);
                        sRotateRRN(root, node);
                        addCounterInt(stats, 3, 1);
                    }
                }
            }
            else
            {
                if (grandparent->L != NULL && grandparent->L->red == 1)
                {
                    parent->red = 0;
                    grandparent->L->red = 0;
                    if (grandparent->P != NULL)
                        grandparent->red = 1;
                }
                else
                {
                    if (parent->R != node)
                    {
                        node->red = 0;
                        node->P->P->red = 1;
                        sRotateRRN(root, node);
                        sRotateLRN(root, node);
                        addCounterInt(stats, 3, 1);
                    }
                    else
                    {
                        node->P->red = 0;
                        node->P->P->red = 1;
                        sRotateLRN(root, node->P);
                        addCounterInt(stats, 3, 1);
                    }
                }
            }
        }
        VerifyRN(root, node->P, stats);
    }
}

RN *_insertRN(RN *node, RN **root, RN *parent, Typeinfo info, RN **start, TreeStats *stats)
{
    if (node == NULL)
    {
        RN *newNode = malloc(sizeof(RN));
        newNode->P = parent;
        newNode->info = info;
        newNode->L = NULL;
        newNode->R = NULL;
        newNode->red = (parent == NULL) ? 0 : 1;
        *start = newNode;
        return newNode;
    }
    else
    {
        if (strcmp(node->info.name, info.name) > 0)
        {
            node->L = _insertRN(node->L, root, node, info, start, stats);
        }
        else if (strcmp(node->info.name, info.name) < 0)
        {
            node->R = _insertRN(node->R, root, node, info, start, stats);
        }

        return node;
    }
}

int insertRN(RN **root, Typeinfo info, TreeStats *stats)
{
    RN *newNode = NULL;
    *root = _insertRN(*root, root, NULL, info, &newNode, stats);
    VerifyRN(root, newNode, stats);
    return 1;
}
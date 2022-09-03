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

RN *_insertRN(RN **root, Typeinfo info, TreeStats *stats)
{

    if (*root == NULL)
    {
        *root = (RN *)malloc(sizeof(RN)); // Aloca memoria para a raiz
        if (*root == NULL)
        {
            return NULL; // Retorna NULL para indicar que nao foi possivel alocar memoria
        }
        (*root)->P = NULL;    // Atribui NULL para o pai da raiz
        (*root)->info = info; // Insere o valor na raiz
        (*root)->L = NULL;    // Insere NULL na esquerda
        (*root)->R = NULL;    // Insere NULL na direita
        (*root)->red = 0;     // Atribui 0 para a cor da raiz
        return *root;         // Retorna a raiz
    }
    else if (strcmp((*root)->info.name, info.name) > 0)
    {
        if ((*root)->L == NULL)
        {
            (*root)->L = malloc(sizeof(RN)); // Aloca memoria para o novo no
            if ((*root)->L == NULL)
            {
                return NULL; // Retorna NULL para indicar que nao foi possivel alocar memoria
            }
            (*root)->L->P = *root;   // Atribui NULL para o pai do no
            (*root)->L->info = info; // Insere o valor no no
            (*root)->L->L = NULL;    // Insere NULL na esquerda
            (*root)->L->R = NULL;    // Insere NULL na direita
            (*root)->L->red = 1;     // Atribui 1 para a cor da raiz
            return (*root)->L;       // Retorna a raiz
        }
        else
        {
            return _insertRN(&(*root)->L, info, stats);
        }
    }
    else if (strcmp((*root)->info.name, info.name) < 0)
    {
        if ((*root)->R == NULL)
        {
            (*root)->R = malloc(sizeof(RN));
            if ((*root)->R == NULL)
            {
                return NULL; // Retorna NULL para indicar que nao foi possivel alocar memoria
            }
            (*root)->R->P = *root;   // Atribui NULL para o pai do no
            (*root)->R->info = info; // Insere o valor no no
            (*root)->R->L = NULL;    // Insere NULL na esquerda
            (*root)->R->R = NULL;    // Insere NULL na direita
            (*root)->R->red = 1;     // Atribui 1 para a cor da raiz
            return (*root)->R;       // Retorna a raiz
        }
        else
        {
            return _insertRN(&(*root)->R, info, stats); // Chama a funcao recursivamente
        }
    }
    else
    {
        return NULL; // Retorna NULL para indicar que o valor ja existe na arvore
    }
}

int insertRN(RN **root, Typeinfo info, TreeStats *stats)
{
    RN *new = _insertRN(root, info, stats);
    if (new != NULL)
    {
        VerifyRN(root, new, stats);

        return 1;
    }
    else
    {
        return 0;
    }
}
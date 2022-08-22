#include "AVL.h"

typedef Food Typeinfo;

typedef struct AVL
{
    Typeinfo info;
    struct AVL *L;
    struct AVL *R;
    int k;
}AVL;

int Factor(AVL *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return heightTree(root->L) - heightTree(root->R);
}

AVL *sRotateR(AVL *root)
{
    AVL *temp = root->L;
    root->L = temp->R;
    temp->R = root;
    root->k = 0;
    root = temp;
    return root;
}

AVL *sRotateL(AVL *root)
{
    AVL *temp = root->R;
    root->R = temp->L;
    temp->L = root;
    root->k = 0;
    root = temp;
    return root;
}

AVL *dRotateoR(AVL *root)
{
    AVL *temp = root->L;
    AVL *temp2 = temp->R;
    temp->R = temp2->L;
    temp2->L = temp;
    root->L = temp2->R;
    temp2->R = root;
    if (temp2->k == 1)
        root->k = -1;
    else
        root->k = 0;
    if (temp2->k == -1)
        temp->k = 1;
    else
        temp->k = 0;
    root = temp2;
    return root;
}

AVL *dRotateL(AVL *root)
{
    AVL *temp = root->R;
    AVL *temp2 = temp->L;
    temp->L = temp2->R;
    temp2->R = temp;
    root->R = temp2->L;
    temp2->L = root;
    if (temp2->k == -1)
        root->k = 1;
    else
        root->k = 0;
    if (temp2->k == 1)
        temp->k = -1;
    else
        temp->k = 0;
    root = temp2;
    return root;
}

AVL *Case1(AVL *root, TreeStats *stats, int *ok)
{
    AVL *temp = root->L;
    if (temp->k == 1)
    {
        addCounterInt(stats, 3, 1);
        root = sRotateR(root);
    }
    else
    {
        addCounterInt(stats, 3, 2);
        root = dRotateoR(root);
    }
    root->k = 0;
    *ok = 0;
    return root;
}

AVL *Case2(AVL *root, TreeStats *stats, int *ok)
{
    AVL *temp = root->R;
    if (temp->k == -1)
    {
        addCounterInt(stats, 3, 1);
        root = sRotateL(root);
    }
    else
    {
        addCounterInt(stats, 3, 2);
        root = dRotateL(root);
    }
    root->k = 0;
    *ok = 0;
    return root;
}

AVL *_insertAVL(AVL *root, Typeinfo info, TreeStats *stats, int *ok)
{
    if (root == NULL)
    {
        root = (AVL *)malloc(sizeof(AVL));
        root->info = info;
        root->L = NULL;
        root->R = NULL;
        root->k = 0;
        *ok = 1;
    }
    else if (strcmp(root->info.name, info.name) > 0)
    {
        root->L = _insertAVL(root->L, info, stats, ok);
        if (*ok)
        {
            switch (root->k)
            {
            case -1:
                root->k = 0;
                *ok = 0;
                break;
            case 0:
                root->k = 1;
                break;
            case 1:
                root = Case1(root, stats, ok);
                break;
            }
        }
    }
    else
    {
        root->R = _insertAVL(root->R, info, stats, ok);
        if (*ok)
        {
            switch (root->k)
            {
            case 1:
                root->k = 0;
                *ok = 0;
                break;
            case 0:
                root->k = -1;
                break;
            case -1:
                root = Case2(root, stats, ok);
                break;
            }
        }
    }
    return root;
}

int insertAVL(AVL **root, Typeinfo info, TreeStats *stats)
{
    int ok = 0;
    *root = _insertAVL(*root, info, stats, &ok);
    return ok;
}

int removeAVL(AVL **root, Typeinfo info, TreeStats *stats)
{
    int retValue = 0;
    if (*root == NULL)
    {
        return 0;
    }
    else if (strcmp((*root)->info.name, info.name) > 0)
    {
        retValue = removeAVL(&(*root)->L, info, stats);
        addCounterInt(stats, 4, 1);
        (*root)->k = Factor(*root);
        if ((*root)->k == 2)
        {
            addCounterInt(stats, 3, 1);
            if (Factor((*root)->L) == 1)
            {
                *root = sRotateR(*root);
            }
            else
            {
                *root = dRotateoR(*root);
            }
        }
        return retValue;
    }
    else if (strcmp((*root)->info.name, info.name) < 0)
    {
        retValue = removeAVL(&(*root)->R, info, stats);
        addCounterInt(stats, 4, 1);
        (*root)->k = Factor(*root);
        if ((*root)->k == -2)
        {
            addCounterInt(stats, 3, 1);
            if (Factor((*root)->R) == -1)
            {
                *root = sRotateL(*root);
            }
            else
            {
                *root = dRotateL(*root);
            }
        }
        return retValue;
    }
    else
    {
        addCounterInt(stats, 4, 1);
        if ((*root)->L == NULL && (*root)->R == NULL)
        {
            retValue = 1;
            free(*root);
            *root = NULL;
            return retValue;
        }
        else if ((*root)->L == NULL)
        {
            retValue = 1;
            AVL *temp = *root;
            *root = (*root)->R;
            free(temp);
            return retValue;
        }
        else if ((*root)->R == NULL)
        {
            retValue = 1;
            AVL *temp = *root;
            *root = (*root)->L;
            free(temp);
            return retValue;
        }
        else
        {
            AVL *temp = (*root)->L;
            while (temp->R != NULL)
            {
                temp = temp->R;
            }
            (*root)->info = temp->info;
            retValue = removeAVL(&(*root)->L, temp->info, stats);
            addCounterInt(stats, 4, 1);
            (*root)->k = Factor(*root);
            if ((*root)->k == 2)
            {
                addCounterInt(stats, 3, 1);
                if (Factor((*root)->L) == 1)
                {
                    *root = sRotateR(*root);
                }
                else
                {
                    *root = dRotateoR(*root);
                }
            }
            return retValue;
        }
    }
}
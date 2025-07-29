#include "AVL.h"

typedef struct AVL
{
    Typeinfo info; // Informação do nó
    struct AVL *L; // Ponteiro para o filho da esquerda
    struct AVL *R; // Ponteiro para o filho da direita
    int k;        // Fator de balanceamento
}AVL;

// Função para calcular o fator de balanceamento
int Factor(AVL *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return heightTree(root->L) - heightTree(root->R);
}

// Função para rotacionar a arvore para a direita
AVL *sRotateRAVL(AVL *root)
{
    AVL *temp = root->L;
    root->L = temp->R;
    temp->R = root;
    root->k = 0;
    root = temp;
    return root;
}

// Função para rotacionar a arvore para a esquerda
AVL *sRotateLAVL(AVL *root)
{
    AVL *temp = root->R;
    root->R = temp->L;
    temp->L = root;
    root->k = 0;
    root = temp;
    return root;
}

// Função para rotacionar a arvore para a direita e depois para a esquerda
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

// Função para rotacionar a arvore para a esquerda e depois para a direita
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
        root = sRotateRAVL(root);
    }
    else
    {
        addCounterInt(stats, 3, 1);
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
        root = sRotateLAVL(root);
    }
    else
    {
        addCounterInt(stats, 3, 1);
        root = dRotateL(root);
    }
    root->k = 0;
    *ok = 0;
    return root;
}

// Função para inserir um elemento na arvore
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

// Função publica para inserir um elemento na arvore
int insertAVL(AVL **root, Typeinfo info, TreeStats *stats)
{
    int ok = 0;
    *root = _insertAVL(*root, info, stats, &ok);
    return ok;
}
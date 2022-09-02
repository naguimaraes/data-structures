#include "Splay.h"

typedef struct Splay
{
    Typeinfo info;
    struct Splay *L;
    struct Splay *R;
} Splay;

Splay *Novo(Typeinfo info, Splay *L, Splay *R);
Splay *Insere(Splay *root, Typeinfo info, TreeStats *stats);
Splay *SplayFun(Splay *root, Typeinfo info, TreeStats *stats);
Splay *Consulta(Splay *root, Typeinfo info, TreeStats *stats);

// Fun��es Auxiliares
Splay *RotL(Splay *root);
Splay *RotR(Splay *root);
Splay *ConsultaSplay(Splay *root, Typeinfo info, TreeStats *stats); // Auxiliar do Inserem, al�m de fazer o Splay Insere o elemento.

int insertSplay(Splay **root, Typeinfo info, TreeStats *stats)
{
    *root = Insere(*root, info, stats);
    return 1;
}

Splay *searchSplay(Splay **inputTree, Typeinfo info, TreeStats *stats)
{
    
    *inputTree = Consulta(*inputTree, info, stats);
    return *inputTree;
}

Splay *Novo(Typeinfo info, Splay *L, Splay *R)
{
    Splay *x = (Splay *)malloc(sizeof(Splay));
    x->info = info;
    x->L = L;
    x->R = R;
    return x;
};

Splay *Insere(Splay *root, Typeinfo info, TreeStats *stats)
{
    return SplayFun(root, info, stats);
};

Splay *Consulta(Splay *root, Typeinfo info, TreeStats *stats)
{
    if (root == NULL)
        return NULL;
    root = ConsultaSplay(root, info, stats);
    return root;
};

Splay *RemoveSplay(Splay *root, Typeinfo info, TreeStats *stats)
{
    Splay *aux;
    if (root == NULL)
        return NULL;
    root = Consulta(root, info, stats);
    if (strcmp(info.name, root->info.name) == 0)
    { /* achou */
        if (root->L == NULL)
        {
            aux = root->R;
        }
        else
        {
            aux = Consulta(root->L, info, stats);
            aux->R = root->R;
        }
        free(root);
        return aux;
    }
    return root; /* It wasn't there */
};

Splay *SplayFun(Splay *root, Typeinfo info, TreeStats *stats)
{
    if (root == NULL)
        return Novo(info, NULL, NULL);
    if (strcmp(info.name, root->info.name) < 0)
    {
        if (root->L == NULL)
            return Novo(info, NULL, root);
        addCounterInt(stats, 3, 1);
        if (strcmp(info.name, root->L->info.name) < 0)
        {
            root->L->L = SplayFun(root->L->L, info, stats);
            root = RotR(root);
        }
        else
        {
            root->L->R = SplayFun(root->L->R, info, stats);
            
            root->L = RotL(root->L);
        }
        return RotR(root);
    }
    else
    {
        if (root->R == NULL)
            return Novo(info, root, NULL);
        addCounterInt(stats, 3, 1);
        if (strcmp(root->R->info.name, info.name) < 0)
        {
            root->R->R = SplayFun(root->R->R, info, stats);
            root = RotL(root);
        }
        else
        {
            root->R->L = SplayFun(root->R->L, info, stats);
            root->R = RotR(root->R);
        }
        return RotL(root);
    }
};

Splay *ConsultaSplay(Splay *root, Typeinfo info, TreeStats *stats)
{
    if (root == NULL)
        return NULL;
    addCounterInt(stats, 4, 1);
    if (strcmp(info.name, root->info.name) < 0)
    {
        if (root->L == NULL)
            return root;
        addCounterInt(stats, 4, 1);
        addCounterInt(stats, 3, 1);
        if (strcmp(info.name, root->L->info.name) < 0)
        {
            root->L->L = ConsultaSplay(root->L->L, info, stats);

            root = RotR(root);
            if (root->L == NULL)
                return root;
            else
                return RotR(root);
        }
        else if (strcmp(root->L->info.name, info.name) < 0)
        {
            root->L->R = ConsultaSplay(root->L->R, info, stats);
            
            if (root->L->R != NULL)
                root->L = RotL(root->L);
            return RotR(root);
        }
        else
        {
            return RotR(root);
        }
    }
    else if (strcmp(root->info.name, info.name) < 0)
    {
        if (root->R == NULL)
            return root;

        addCounterInt(stats, 4, 1);
        addCounterInt(stats, 3, 1);
        if (strcmp(root->R->info.name, info.name) < 0)
        {
            root->R->R = ConsultaSplay(root->R->R, info, stats);
            
            root = RotL(root);
            if (root->R == NULL)
                return root;
            else
                return RotL(root);
        }
        else if (strcmp(info.name, root->R->info.name) < 0)
        {
            root->R->L = ConsultaSplay(root->R->L, info, stats);
            if (root->R->L != NULL)
                root->R = RotR(root->R);
            return RotL(root);
        }
        else
        {
            return RotL(root);
        }
    }
    else
        return root;
};

Splay *RotR(Splay *root)
{
    Splay *aux = root->L;
    root->L = aux->R;
    aux->R = root;
    return aux;
};

Splay *RotL(Splay *root)
{
    Splay *aux = root->R;
    root->R = aux->L;
    aux->L = root;
    return aux;
};
/* Ian && Nathan- Cartão UFRGS: 00338368 && ??
15.08.22
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "shared.h" // Funções compartilhadas para criar e fazer o output

#include "ABP.h" // Cria as funções para a arvore ABP
#include "AVL.h" // Cria as funções para a arvore AVL
#include "RN.h" // Cria as funções para a arvore RN
#include "Splay.h" // Cria as funções para a arvore Splay

int main(int argc, char *argv[])
{
    Outputs output; // Cria a struct para o output

    outputStart(argc, argv, &output); // Inicia o output

    Alimento test;
    Ingerido test2 = {" ", 100};
    while (!getAlimento(&test, output.arg1Foods))
    {
        output.totalCals += caloriasIngeridas(test, test2);
        char *test3 = getOutputString(test, test2);
        outputToFile(test3, output.arg3OutputFile);
        free(test3);
    }

    outputEnd(&output); // Finaliza o output

    return 0;
}
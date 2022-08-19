/* Ian && Nathan- Cartão UFRGS:
15.08.22
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "shared.h"

int main(int argc, char *argv[])
{
    FILE *outputFile, *day, *food;
    Counter counter;
    int totalCals = 0;

    outputStart(argc, argv, &outputFile, &day, &food, &counter, &totalCals);

    Alimento test;
    Ingerido test2 = {" ", 100};
    while (!getAlimento(&test, food))
    {
        char *test3 = getOutputString(test, test2);
        outputToFile(test3, outputFile);
        free(test3);
    }

    outputEnd(&outputFile, &day, &food, counter, totalCals);

    return 0;

    
}
#include "shared.h"

void outputStart(int argc, char *argv[], FILE **outputFile, FILE **day, FILE **food, Counter *counter, int *totalCals)
{
    if (argc != 4) 
    {
        printf("Usage: <program> <food file> <day file> <output file>\n");
        exit(1);
    }

    *food = fopen(argv[1], "r");
    if (food == NULL)
    {
        printf("Error: Food file not found.\n");
        exit(2);
    }

    *day = fopen(argv[2], "r");
    if (day == NULL)
    {
        printf("Error: Day file not found.\n");
        exit(3);
    }

    *outputFile = fopen(argv[3], "w");
    if (outputFile == NULL)
    {
        printf("Error: Output file not found.\n");
        exit(4);
    }

    startOutputFile(*outputFile, argv);

    *counter = initCounter();
    *totalCals = 0;
}

void outputEnd(FILE **outputFile, FILE **day, FILE **food, Counter counter, int totalCals)
{
    finishOutputFile(*outputFile, counter, totalCals);

    fclose(*food);
    fclose(*day);
    fclose(*outputFile);
}

float caloriasIngeridas(Alimento Alimento, Ingerido ingerido)
{
    return (Alimento.caloriesPer100Grams / (float)100) * ingerido.quantityInGrams;
}

int getAlimento(Alimento *alimento, FILE *file)
{
    if (alimento == NULL || file == NULL)
    {
        return -1;
    }

    char *temp = (char *)malloc(sizeof(char) * 100);
    if (temp == NULL)
    {
        return -1;
    }

    if (fgets(temp, 100, file) == NULL)
    {
        alimento->name[0] = '\0';
        alimento->caloriesPer100Grams = -1;
        return 1;
    }

    strtok(temp, ";");
    strcpy(alimento->name, temp);
    for (int i = 0; i < strlen(alimento->name); i++) alimento->name[i] = tolower(alimento->name[i]);
    alimento->caloriesPer100Grams = atoi(strtok(NULL, ";"));
    free(temp);

    return 0;
}

int getIngerido(Ingerido *ingerido, FILE *file)
{
    if (ingerido == NULL || file == NULL)
    {
        return -1;
    }

    char *temp = (char *)malloc(sizeof(char) * 100);
    if (fgets(temp, 100, file) == NULL)
    {
        ingerido->name[0] = '\0';
        ingerido->quantityInGrams = -1;
        return 1;
    }

    strcpy(ingerido->name, temp);
    for (int i = 0; i < strlen(ingerido->name); i++) ingerido->name[i] = tolower(ingerido->name[i]);
    ingerido->quantityInGrams = atoi(strtok(NULL, ";"));
    free(temp);
    return 0;
}

char *getOutputString(Alimento alimento, Ingerido ingerido)
{
    char *output = (char *)malloc(sizeof(char) * 100);
    sprintf(output, "%dg de %s (%d calorias por 100g) = %.0f calorias", ingerido.quantityInGrams, alimento.name, alimento.caloriesPer100Grams, caloriasIngeridas(alimento, ingerido));
    return output;
}

int outputToFile(char *output, FILE *file)
{
    if (output == NULL || file == NULL)
    {
        return -1;
    }
    fprintf(file, "%s\n", output);
    return 0;
}

char *printStatistics(Statistics stats)
{
    char *output = (char *)malloc(sizeof(char) * 1000);
    sprintf(output, "========  ESTATÍSTICAS %s  ========\nNúmero de Nodos: %d\nAltura: %d\nRotações: %d\nComparações: %d\n\n", stats.name, stats.numNodes, stats.height, stats.rotations, stats.comparasions);
    return output;
}

int startOutputFile(FILE *file, char *argv[])
{
    fprintf(file, "Calorias caluladas para %s usando a tabela %s.\n\n", argv[2], argv[1]);
    return 0;
}

int finishOutputFile(FILE *file, Counter counter, int totalCals)
{
    fprintf(file, "\n");

    fprintf(file, "Total de %d calorias consumidas no dia.\n\n", totalCals);

    char *output = printStatistics(counter.ABP);
    fprintf(file, "%s\n", output);
    free(output);

    output = printStatistics(counter.AVL);
    fprintf(file, "%s\n", output);
    free(output);

    output = printStatistics(counter.RN);
    fprintf(file, "%s\n", output);
    free(output);

    output = printStatistics(counter.Splay);
    fprintf(file, "%s\n", output);
    free(output);

    return 0;
}

Counter initCounter()
{
    Counter counter;
    counter.ABP = (Statistics){"ABP", 0, 0, 0, 0};
    counter.AVL = (Statistics){"AVL", 0, 0, 0, 0};
    counter.RN = (Statistics){"RN", 0, 0, 0, 0};
    counter.Splay = (Statistics){"Splay", 0, 0, 0, 0};
    return counter;
}
#include "shared.h"

void outputStart(int argc, char *argv[], Outputs *output)
{
    //! CASOS DE ERRO DE ENTRADA E ARQUIVOS
    if (argc != 4) 
    {
        printf("Usage: <program> <food file> <day file> <output file>\n"); // Printa o erro
        exit(1); // Sai do programa
    }

    output->arg1Foods = fopen(argv[1], "r");
    if (output->arg1Foods == NULL)
    {
        printf("Error: Food file not found.\n"); // Printa o erro
        exit(2); // Sai do programa
    }

    output->arg2Day = fopen(argv[2], "r");
    if (output->arg2Day == NULL)
    {
        printf("Error: Day file not found.\n");
        exit(3);
    }

    output->arg3OutputFile = fopen(argv[3], "w");
    if (output->arg3OutputFile == NULL)
    {
        printf("Error: Output file not found.\n");
        exit(4);
    }
    //! FINAL DOS CASOS DE ERRO

    startOutputFile(output->arg3OutputFile, argv); // Inicia o arquivo de saida

    output->counter = initCounter(); // Inicializa os contadores de todas as arvores
    output->totalCals = 0; // Inicializa o total de calorias ingeridas
}

void outputEnd(Outputs *output)
{
    finishOutputFile(output->arg3OutputFile, output->counter, output->totalCals); // Finaliza o arquivo de saida

    fclose(output->arg1Foods); // Fecha o arquivo de alimentos
    fclose(output->arg2Day); // Fecha o arquivo de dias
    fclose(output->arg3OutputFile); // Fecha o arquivo de saida
}

float caloriasIngeridas(Alimento Alimento, Ingerido ingerido)
{
    return (Alimento.caloriesPer100Grams / (float)100) * ingerido.quantityInGrams; // Retorna a quantidade de calorias ingeridas
}

int getAlimento(Alimento *alimento, FILE *file)
{
    if (alimento == NULL || file == NULL)
    {
        return -1; // Retorna -1 se algum parametro for nulo
    }

    char *temp = (char *)malloc(sizeof(char) * 100); // Aloca memoria para o nome do alimento
    if (temp == NULL)
    {
        return -1; // Retorna -1 se nao conseguir alocar memoria
    }

    if (fgets(temp, 100, file) == NULL)
    {
        alimento = NULL; // Inicializa o alimento como nulo
        return 1; // Retorna 1 se chegar no final do arquivo
    }

    strtok(temp, ";"); // Remove o ; do nome do alimento
    strcpy(alimento->name, temp); // Copia o nome do alimento para o struct
    for (int i = 0; i < strlen(alimento->name); i++) alimento->name[i] = tolower(alimento->name[i]); // Converte o nome do alimento para minusculo
    alimento->caloriesPer100Grams = atoi(strtok(NULL, ";")); // Pega a quantidade de calorias por 100 gramas do alimento
    free(temp); // Libera a memoria alocada para o nome do alimento

    return 0; // Retorna 0 se nao houver erros
}

int getIngerido(Ingerido *ingerido, FILE *file)
{
    if (ingerido == NULL || file == NULL)
    {
        return -1;  // Retorna -1 se algum parametro for nulo
    }

    char *temp = (char *)malloc(sizeof(char) * 100); // Aloca memoria para o nome do alimento
    if (temp == NULL)
    {
        return -1; // Retorna -1 se nao conseguir alocar memoria
    }

    if (fgets(temp, 100, file) == NULL) 
    {
        ingerido = NULL; // Inicializa o alimento como nulo
        return 1; // Retorna 1 se chegar no final do arquivo
    }

    strtok(temp, ";");
    strcpy(ingerido->name, temp); // Copia o nome do alimento para o struct
    for (int i = 0; i < strlen(ingerido->name); i++) ingerido->name[i] = tolower(ingerido->name[i]); // Converte o nome do alimento para minusculo
    ingerido->quantityInGrams = atoi(strtok(NULL, ";")); // Pega a quantidade de calorias por 100 gramas do alimento
    free(temp); // Libera a memoria alocada para o nome do alimento

    return 0; // Retorna 0 se nao houver erros
}

char *getOutputString(Alimento alimento, Ingerido ingerido)
{
    char *output = (char *)malloc(sizeof(char) * 100); // Aloca memoria para o nome do alimento
    if (output == NULL)
    {
        return NULL; // Retorna -1 se nao conseguir alocar memoria
    }
    sprintf(output, "%dg de %s (%d calorias por 100g) = %.0f calorias", ingerido.quantityInGrams, alimento.name, alimento.caloriesPer100Grams, caloriasIngeridas(alimento, ingerido)); // Formata a string de saida
    return output; // Retorna a string de saida
}

int outputToFile(char *output, FILE *file)
{
    if (output == NULL || file == NULL)
    {
        return -1; // Retorna -1 se algum parametro for nulo
    }
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo
    return 0; // Retorna 0 se nao houver erros
}

char *printStatistics(Statistics stats)
{
    char *output = (char *)malloc(sizeof(char) * 1000); // Aloca memoria para o nome do alimento
    if (output == NULL)
    {
        return NULL; // Retorna -1 se nao conseguir alocar memoria
    }
    sprintf(output, "========  ESTATÍSTICAS %s  ========\nNúmero de Nodos: %d\nAltura: %d\nRotações: %d\nComparações: %d\n\n", stats.name, stats.numNodes, stats.height, stats.rotations, stats.comparasions);
    return output; // Retorna a string de saida
}

int startOutputFile(FILE *file, char *argv[])
{
    return fprintf(file, "Calorias caluladas para %s usando a tabela %s.\n\n", argv[2], argv[1]); // Escreve o cabecalho do arquivo de saida
}

int finishOutputFile(FILE *file, Counter counter, int totalCals)
{
    fprintf(file, "\nTotal de %d calorias consumidas no dia.\n\n", totalCals); // Escreve o cabecalho do arquivo de saida

    char *output = printStatistics(counter.ABP); // Pega a string de saida do ABP
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo de saida
    free(output); // Libera a memoria alocada para a string de saida

    output = printStatistics(counter.AVL); // Pega a string de saida do AVL
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo de saida
    free(output); // Libera a memoria alocada para a string de saida

    output = printStatistics(counter.RN); // Pega a string de saida do RN
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo de saida
    free(output); // Libera a memoria alocada para a string de saida

    output = printStatistics(counter.Splay); // Pega a string de saida do Splay
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo de saida
    free(output); // Libera a memoria alocada para a string de saida

    return 0; // Retorna 0 se nao houver erros
}

Counter initCounter()
{
    Counter counter; // Inicializa o contador
    counter.ABP = (Statistics){"ABP", 0, 0, 0, 0}; // Inicializa o contador do ABP
    counter.AVL = (Statistics){"AVL", 0, 0, 0, 0}; // Inicializa o contador do AVL
    counter.RN = (Statistics){"RN", 0, 0, 0, 0}; // Inicializa o contador do RN
    counter.Splay = (Statistics){"Splay", 0, 0, 0, 0}; // Inicializa o contador do Splay
    return counter; // Retorna o contador
}
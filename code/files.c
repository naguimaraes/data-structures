#include "files.h"

int getFoodFromFile(Food *food, FILE *file)
{
    if (food == NULL || file == NULL)
    {
        return -1;  // Retorna -1 se algum parametro for nulo
    }

    char temp[1000]; // Variavel para percorrer o arquivo
    if (fgets(temp, 1000, file) == NULL)
    {
        food = NULL;        // Inicializa o alimento como nulo
        return 1;           // Retorna 1 se chegar no final do arquivo
    }
    if (strchr(temp, ';') == NULL)
    {
        food = NULL;        // Inicializa o alimento como nulo
        return 1;           // Retorna 1 se chegar no final do arquivo
    }
    
    strtok(temp, ";");                                                                      // Remove o ; do nome do alimento
    strcpy(food->name, temp);                                                               // Copia o nome do alimento para o struct
    for (int i = 0; i < strlen(food->name); i++) food->name[i] = tolower(food->name[i]);    // Converte o nome do alimento para minusculo
    food->calories = atoi(strtok(NULL, ";"));                                               // Pega a quantidade de calorias por 100 gramas do alimento

    return 0; // Retorna 0 se nao houver erros
}

char *getOutputString(Food alimento, Food ingerido)
{
    char *output = (char *)malloc(sizeof(char) * 100); // Aloca memoria para a string de saida
    if (output == NULL)
    {
        return NULL; // Retorna NULL se nao conseguir alocar memoria
    }
    sprintf(output, "%dg de %s (%d calorias por 100g) = %d calorias", ingerido.calories, alimento.name, alimento.calories, calsIngested(alimento, ingerido)); // Formata a string de saida
    return output;                                                                                                                                                                       // Retorna a string de saida
}

char *printStatistics(TreeStats stats)
{
    char *output = (char *)malloc(sizeof(char) * 1000); // Aloca memoria para o nome do alimento
    if (output == NULL)
    {
        return NULL; // Retorna NULL se nao conseguir alocar memoria
    }
    int numNodes = getCounterInt(&stats, 1);
    int height = getCounterInt(&stats, 2);
    int rotations = getCounterInt(&stats, 3);
    int comparasions = getCounterInt(&stats, 4);
    sprintf(output, "========  ESTATÍSTICAS %s ============\nNumero de Nodos: %d\nAltura: %d\nRotações: %d\nComparações: %d\n", getCounterName(&stats), numNodes, height, rotations, comparasions);
    return output; // Retorna a string de saida
}

Outputs initOutput(int argc, char *argv[])
{
    Outputs output; // Cria a struct para o output
    //! CASOS DE ERRO DE ENTRADA E ARQUIVOS
    if (argc != 4)
    {
        printf("Usage: <program> <food file> <day file> <output file>\n"); // Printa o erro
        printf("Press Enter to Exit.");
        getc(stdin);                                                      // Pausa o programa
        exit(1);                                                           // Sai do programa
    }
    FILE *foodFile = fopen(argv[1], "r"); // Abre o arquivo de alimentos
    if (foodFile == NULL)
    {
        printf("Error: Food file not found.\n"); // Printa o erro
        printf("Press Enter to Exit.");
        getc(stdin);                             // Pausa o programa
        exit(2);                                 // Sai do programa
    }

    FILE *dayFile = fopen(argv[2], "r"); // Abre o arquivo de dias
    if (dayFile == NULL)
    {
        printf("Error: Day file not found.\n");
        printf("Press Enter to Exit.");
        getc(stdin); // Pausa o programa
        exit(3);
    }

    FILE *outputFile = fopen(argv[3], "w"); // Abre o arquivo de saida
    if (outputFile == NULL)
    {
        printf("Error: Output file not found.\n");
        printf("Press Enter to Exit.");
        getc(stdin); // Pausa o programa
        exit(4);
    }
    //! FINAL DOS CASOS DE ERRO

    fprintf(outputFile, "Calorias calculadas para %s usando a tabela %s.\n\n", argv[2], argv[1]); // Escreve o cabecalho do arquivo de saida

    setFilePointer(&output, 1, foodFile); // Move o ponteiro do arquivo de alimentos para o primeiro alimento
    setFilePointer(&output, 2, dayFile); // Move o ponteiro do arquivo de dias para o primeiro dia
    setFilePointer(&output, 3, outputFile); // Move o ponteiro do arquivo de saida para o primeiro alimento
    
    output.stats[0] = initCounter("ABP"); // Inicializa os contadores de todas as arvores
    output.stats[1] = initCounter("AVL");
    output.stats[2] = initCounter("RN");
    output.stats[3] = initCounter("Splay");
    output.totalCals = 0;           // Inicializa o total de calorias ingeridas
    return output;                  // Retorna a struct de output
}

void deletOutput(Outputs *output)
{
    FILE *file = getFilePointer(output, 3); // Muda a nomeclatura do arquivo de saida

    fprintf(file, "\nTotal de %d calorias consumidas no dia.\n\n", getCals(output)); // Escreve o cabecalho do arquivo de saida

    TreeStats ABP = *getTreeStats(output, 1); // Pega as estatisticas da arvore
    char *outputString = printStatistics(ABP); // Pega a string de saida do ABP
    fprintf(file, "%s\n\n", outputString);       // Escreve a string de saida no arquivo de saida
    free(outputString);                        // Libera a memoria alocada para a string de saida

    TreeStats AVL = *getTreeStats(output, 2); // Pega as estatisticas da arvore
    outputString = printStatistics(AVL);   // Pega a string de saida do AVL
    fprintf(file, "%s\n\n", outputString);         // Escreve a string de saida no arquivo de saida
    free(outputString);                          // Libera a memoria alocada para a string de saida

    TreeStats RN = *getTreeStats(output, 3);  // Pega as estatisticas da arvore
    outputString = printStatistics(RN); // Pega a string de saida do RN
    fprintf(file, "%s\n\n", outputString);        // Escreve a string de saida no arquivo de saida
    free(outputString);                         // Libera a memoria alocada para a string de saida

    TreeStats Splay = *getTreeStats(output, 4); // Pega as estatisticas da arvore
    outputString = printStatistics(Splay); // Pega a string de saida do Splay
    fprintf(file, "%s", outputString);           // Escreve a string de saida no arquivo de saida
    free(outputString);                            // Libera a memoria alocada para a string de saida

    fclose(getFilePointer(output, 1));      // Fecha o arquivo de alimentos
    fclose(getFilePointer(output, 2));      // Fecha o arquivo de dias
    fclose(getFilePointer(output, 3));      // Fecha o arquivo de saida
}

int outputStringToFile(char *output, FILE *file)
{
    if (output == NULL || file == NULL)
    {
        return -1; // Retorna -1 se algum parametro for nulo
    }
    fprintf(file, "%s\n", output); // Escreve a string de saida no arquivo
    return 0;                      // Retorna 0 se nao houver erros
}
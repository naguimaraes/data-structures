/* 
    Ian && Nathan - UFRGS ID: 00338368 && 00334437
    15.08.22
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
 
#include "include/files.h" // Functions to write the files
#include "include/types.h" // Structs and functions for structs
#include "include/trees.h" // Shared function between trees

// Tree functions
#include "structures/ABP.h" // Creates functions for the BST tree
#include "structures/AVL.h" // Creates functions for the AVL tree
#include "structures/RN.h" // Creates functions for the RB tree
#include "structures/Splay.h" // Creates functions for the Splay tree
#include "structures/LSE.h" // Creates functions for the singly linked list

int main(int argc, char *argv[])
{
    printf("Initializing program...\n");
    
    // Add argv treatment for input and output files
    if (argc < 4) {
        printf("Usage: %s <food_file> <ingested_file> <output_file>\n", argv[0]);
        printf("Please provide all required files:\n");
        printf("  - Food database file\n");
        printf("  - Ingested food file\n");
        printf("  - Output file\n");
        return 1;
    }
    
    // Validate file arguments
    for (int i = 1; i < argc - 1; i++) { // Check input files (exclude output file)
        FILE *testFile = fopen(argv[i], "r");
        if (testFile == NULL) {
            printf("Error: Cannot open input file '%s'\n", argv[i]);
            return 1;
        }
        fclose(testFile);
    }

    Outputs output = initOutput(argc, argv); // Creates the struct for output
    printf("\nProgram initilization successful!\n"); // Prints status message

    TreeStats *statsABP = getTreeStats(&output, 1);                 // Creates the struct for BST tree counter
    TreeStats *statsAVL = getTreeStats(&output, 2);                 // Creates the struct for AVL tree counter
    TreeStats *statsRN = getTreeStats(&output, 3);               // Creates the struct for RB tree counter
    TreeStats *statsSplay = getTreeStats(&output, 4);            // Creates the struct for Splay tree counter
    TreeStats *statsLSE = getTreeStats(&output, 5);              // Creates the struct for LSE tree counter

    printf("\nBuilding trees...\n");
    ABP *ABPtree = createTree(); // Creates the BST tree
    AVL *AVLtree = createTree(); // Creates the AVL tree
    RN *RNtree = createTree(); // Creates the RB tree
    Splay *Splaytree = createTree(); // Creates the Splay tree
    LSE *LSEtree = createList(); // Creates the LSE list
    printf("\nTrees created!\n");

    Food food;
    printf("\nReading food file...\n");
    while (!getFoodFromFile(&food, getFilePointer(&output, 1)))
    {
        insertABP(&ABPtree, food, statsABP); // Inserts food into BST tree
        insertAVL(&AVLtree, food, statsAVL); // Inserts food into AVL tree
        insertRN(&RNtree, food, statsRN); // Inserts food into RB tree
        insertSplay(&Splaytree, food, statsSplay); // Inserts food into Splay tree
        insertLSEEnd(&LSEtree, food, statsLSE); // Inserts food into LSE list
    }
    printf("\nFood file read!\n");

    Food ingested; // Creates the food that will be ingested
    printf("\nReading ingested food file and comparing...\n");
    while (!getFoodFromFile(&ingested, getFilePointer(&output, 2)))
    {
        ABP *nodeABP = consulta(ABPtree, ingested, statsABP);           // Searches for food in BST tree
        AVL *nodeAVL = consulta(AVLtree, ingested, statsAVL);           // Searches for food in AVL tree
        RN *nodeRN = consulta(RNtree, ingested, statsRN);               // Searches for food in RB tree
        Splay *nodeSplay = searchSplay(&Splaytree, ingested, statsSplay); // Searches for food in Splay tree
        LSE *nodeLSE = searchLSE(LSEtree, ingested, statsLSE);           // Searches for food in LSE list

        if (nodeABP != NULL && nodeAVL != NULL && nodeRN != NULL && nodeSplay != NULL && nodeLSE != NULL)
        {
            Food temp = getInfo(nodeABP); // Gets food from BST tree, since all found it, all "foods" are equal
            
            addCals(&output, calsIngested(temp, ingested)); // Adds food calories to total calories
            
            char *outputString = getOutputString(temp, ingested); // Gets output string
            outputStringToFile(outputString, getFilePointer(&output, 3)); // Writes string to output file
            free(outputString); // Frees the string
        }
    }
    printf("\nIngested food file read!\n");

    printf("\nUpdating tree stats...\n");
    updateTreeCounter(statsABP, ABPtree); // Updates BST statistics
    updateTreeCounter(statsAVL, AVLtree); // Updates AVL statistics
    updateTreeCounter(statsRN, RNtree); // Updates RB statistics
    updateTreeCounter(statsSplay, Splaytree); // Updates Splay statistics

    printf("\nDeleting trees...\n");
    deletTree(&ABPtree); // Destroys BST tree
    deletTree(&AVLtree); // Destroys AVL tree
    deletTree(&RNtree); // Destroys RB tree
    deletTree(&Splaytree); // Destroys Splay tree
    deletList(&LSEtree); // Destroys LSE list

    printf("\nWriting output file...\n");
    deletOutput(&output); // Finalizes output file

    printf("\nProgram finished!\n");
    
    return 0;
}

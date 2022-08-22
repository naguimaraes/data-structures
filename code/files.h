#ifndef FILES_H_
#define FILES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

// Return from the parameter the food from the line where file is, returns a 0 if sucessful, -1 if error, 1 and food as NULL if end of file
int getFoodFromFile(Food *food, FILE *file);

// Return the pointer to the allocated string with the output string, returns NULL if error
char *getOutputString(Food alimento, Food ingerido);

// Return the pointer to the allocated string with the statistics, returns NULL if error
char *printStatistics(TreeStats stats);

// Starts all the needed setup for writing to files and the output strings and counters
Outputs initOutput(int argc, char *argv[]);

// Writes all the output string to the files and end the file streams
void deletOutput(Outputs *output);

// Writes the output string to the file
int outputStringToFile(char *output, FILE *file);

#endif // FILES_H_
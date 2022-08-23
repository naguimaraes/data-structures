#include "types.h"

TreeStats initCounter(char name[])
{
    TreeStats stats;
    strcpy(stats.name, name);
    stats.counters[0] = 0;
    stats.counters[1] = 0;
    stats.counters[2] = 0;
    stats.counters[3] = 0;
    return stats;
}

int *getCounterIntPointer(TreeStats *stats, int index)
{
    if (index < 1 || index > 4)
    {
        return NULL;
    }
    return &(stats->counters[index - 1]);
}

int getCounterInt(TreeStats *stats, int index)
{
    if (index < 1 || index > 4)
    {
        return 0;
    }
    return (stats->counters[index - 1]);
}

char *getCounterName(TreeStats *stats)
{
    return stats->name;
}

void setCounterName(TreeStats *stats, char name[])
{
    strcpy(stats->name, name);
}

void addCounterInt(TreeStats *stats, int index, int value)
{
    if (index < 1 || index > 4)
    {
        return;
    }
    stats->counters[index - 1] += value;
}

TreeStats *getTreeStats(Outputs *counters, int index)
{
    if (index < 1 || index > 4)
    {
        return NULL;
    }
    return &(counters->stats[index - 1]);
}

FILE *getFilePointer(Outputs *output, int index)
{
    if (index < 1 || index > 3)
    {
        return NULL;
    }
    return output->file[index - 1];
}

void setFilePointer(Outputs *output, int index, FILE *file)
{
    if (index < 1 || index > 3)
    {
        return;
    }
    output->file[index - 1] = file;
}

void addCals(Outputs *output, float cals)
{
    output->totalCals += cals;
}

int getCals(Outputs *output)
{
    return output->totalCals;
}

char *getFoodName(Food *food)
{
    return food->name;
}

int getFoodCals(Food *food)
{
    return food->calories;
}

void setFoodName(Food *food, char name[])
{
    strcpy(food->name, name);
}

void setFoodCals(Food *food, int cals)
{
    food->calories = cals;
}

int calsIngested(Food food, Food ingested)
{
    return food.calories / (float)100 * ingested.calories;
}
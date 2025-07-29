# Performance Comparison Between Different Data Structures

## Project Overview

This project was developed as the final project for the Data Structures course at UFRGS, developed by [Ian Kersz Amaral](https://github.com/kerszamaral) and [Nathan Alonso Guimarães](https://github.com/naguimaraes). It implements different data structures and compares their performance for storing and searching food information. The program reads a database of 1000 different foods with their caloric values and processes daily food consumption data to calculate total calories consumed, while measuring the performance metrics of each data structure. The final results and analysis are presented in the project [report file](Report.pdf).

The project was originally conceived in August of 2022, but it has been updated in July of 2025 to be better documented in GitHub. Minor changes were made to the code, trying to preserve the original work while improving the documentation and usability.

## Features

- **Food Database Management**: Reads and stores food items with their caloric information
- **Performance Metrics**: Tracks and compares:
  - Number of nodes
  - Tree height
  - Number of rotations performed
  - Number of comparisons made during searches
- **Calorie Calculation**: Processes daily food consumption and calculates total calories
- **Comprehensive Output**: Generates detailed statistics for each data structure

## Data Structures Implemented

The project implements five different data structures:

1. **ABP (Árvore Binária de Pesquisa)**: Binary Search Tree
2. **AVL (Adelson-Velsky and Landis)**: Self-balancing Binary Search Tree (AVL Tree)
3. **RN (Rubro-Negro)**: Red-Black Tree
4. **Splay**: Splay Tree
5. **LSE (Lista Simplesmente Encadeada)**: Singly Linked List

## File Structure

```text
├── data/
│   ├── 1000Sorted.csv    # Food database (sorted)
│   ├── 1000Shuffled.csv  # Food database (shuffled)
│   └── day1.csv          # Example of a daily food consumption data
├── include/
│   ├── files.c/.h        # File I/O operations
│   ├── trees.c/.h        # Common tree functions
│   └── types.c/.h        # Data structures and utility functions
├── structures/
│   ├── ABP.c/.h          # Binary Search Tree implementation
│   ├── AVL.c/.h          # AVL Tree implementation
│   ├── LSE.c/.h          # Linked List implementation
│   ├── RN.c/.h           # Red-Black Tree implementation
│   └── Splay.c/.h        # Splay Tree implementation
├── output/
│   └── *.txt             # Output files
├── data-structures.exe   # Executable after building
├── main.c                # Main program file
├── Makefile              # Build configuration
├── README.md             # Project documentation
├── Report.pdf            # Project report in Portuguese
└── Specification.pdf     # Project requirements in Portuguese
```

## Building and Running the Project

### Repository Setup

To set up the repository, clone and access it using:

```bash
git clone https://github.com/naguimaraes/data-structures.git
cd data-structures
```

### Makefile Targets

Here are all available Makefile targets commands:

- `make` - Build the project (default)
- `make run` - Run with both shuffled and sorted data
  - `make run-shuffled` - Run with shuffled data
  - `make run-sorted` - Run with sorted data
- `make clean` - Remove all built files
- `make help` - Show available targets

### Building the Project

To build the project, simply run:

```bash
make
```

To build manually, compile the main program with:

```bash
gcc -o data-structures.exe main.c include/*.c structures/*.c -I include
```

### Running the Program

1. To run and generate both shuffled and sorted outputs, use:

```bash
make run
```

2. To run and generate the shuffled output, use:

```bash
make run-shuffled
```

3. To run and generate the sorted output, use:

```bash
make run-sorted
```

4. Or run manually with:

```bash
./data-structures.exe <food_database.csv> <daily_consumption.csv> <output_file.txt>

# Example Usage
./data-structures.exe data/1000Sorted.csv data/day1.csv /output/output.txt
```

## Input File Format

### Food Database (CSV format)

```csv
Food Name,Calories per 100g
Apple,52
Banana,89

...

Rice,130
// EOF
```

### Daily Consumption (CSV format)

```csv
Food Name,Grams Consumed
Apple,150
Rice,200

...

Banana,120
// EOF
```

## Output

The program generates a comprehensive report including:

- List of consumed foods with calculated calories
- Total daily calorie consumption
- Performance statistics for each data structure:
  - Number of nodes
  - Tree height
  - Number of rotations
  - Number of comparisons

### Output Example

```text
150g de activia (74 calorias por 100g) = 111 calorias
110g de tangerine (53 calorias por 100g) = 58 calorias
120g de bagel (257 calorias por 100g) = 308 calorias

...

============  ESTATÍSTICAS ABP ============
Numero de Nodos: 1000
Altura: 22
Rotações: 0
Comparações: 144

...

// EOF
```

## Performance Analysis

The project allows comparison of different data structures in terms of:

- **Search efficiency**: Number of comparisons needed to find elements
- **Memory usage**: Tree height and structure complexity
- **Maintenance cost**: Number of rotations required for balanced trees

## Technical Implementation Details

- **Language**: C (C99 standard)
- **Memory Management**: Dynamic allocation with proper cleanup
- **Error Handling**: Error checking for file operations and memory allocation
- **Modular Design**: Separate modules for each data structure with common interfaces

## License

This project is part of academic coursework at UFRGS and is intended for educational purposes.

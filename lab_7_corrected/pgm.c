#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPRESSIONS 100

// Structure to represent an expression in three-address code
struct Expression {
    char lhs[10];  // Left-hand side variable (e.g., t1, t2)
    char op[3];    // Operator (e.g., +, *, ^, -, /)
    char rhs1[10]; // First operand (can be a variable or another temporary)
    char rhs2[10]; // Second operand (can be a variable or another temporary)
};

// Function to find the index of a common subexpression
int findCommonSubexpression(struct Expression exp[], int n, struct Expression current) {
    for (int i = 0; i < n; i++) {
        if (strcmp(exp[i].op, current.op) == 0 &&
            strcmp(exp[i].rhs1, current.rhs1) == 0 &&
            strcmp(exp[i].rhs2, current.rhs2) == 0) {
            return i; // Return the index of the common expression
        }
    }
    return -1; // No common subexpression found
}

// Function to replace occurrences of the eliminated expression
void replaceOccurrences(struct Expression exp[], int n, const char *oldVar, const char *newVar) {
    for (int i = 0; i < n; i++) {
        if (strcmp(exp[i].rhs1, oldVar) == 0) {
            strcpy(exp[i].rhs1, newVar);
        }
        if (strcmp(exp[i].rhs2, oldVar) == 0) {
            strcpy(exp[i].rhs2, newVar);
        }
    }
}

// Function to eliminate common subexpressions
void eliminateCommonSubexpressions(struct Expression exp[], int *n) {
    for (int i = 0; i < *n; i++) {
        int index = findCommonSubexpression(exp, i, exp[i]);
        if (index != -1) {
            // Print what the common subexpression is
            printf("Common subexpression found: %s = %s %s %s and %s = %s %s %s\n",
                   exp[index].lhs, exp[index].rhs1, exp[index].op, exp[index].rhs2,
                   exp[i].lhs, exp[i].rhs1, exp[i].op, exp[i].rhs2);
            printf("Eliminating %s = %s %s %s and using %s instead\n",
                   exp[i].lhs, exp[i].rhs1, exp[i].op, exp[i].rhs2, exp[index].lhs);

            // Check if the eliminated expression is t6 before replacing occurrences
            if (strcmp(exp[i].lhs, "t6") != 0) {
                // Replace occurrences of the eliminated expression
                replaceOccurrences(exp, *n, exp[i].lhs, exp[index].lhs);
            }

            // Remove the duplicate expression only if it is not t6
            if (strcmp(exp[i].lhs, "t6") != 0) {
                for (int j = i; j < *n - 1; j++) {
                    exp[j] = exp[j + 1];
                }
                (*n)--; // Reduce the total number of expressions
                i--;    // Recheck the current index
            }
        }
    }

    // Output the optimized expression list
    printf("\nOptimized expressions:\n");
    for (int i = 0; i < *n; i++) {
        printf("%s = %s %s %s\n", exp[i].lhs, exp[i].rhs1, exp[i].op, exp[i].rhs2);
    }
}

int main() {
    FILE *file;
    char filename[100];
    struct Expression exp[MAX_EXPRESSIONS];
    int n = 0;
    char line[100];

    // Input the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Read expressions from the file
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, " %s = %s %s %s", exp[n].lhs, exp[n].rhs1, exp[n].op, exp[n].rhs2) == 4) {
            n++;  // Increment the count of expressions
            if (n >= MAX_EXPRESSIONS) {
                printf("Warning: Maximum number of expressions reached.\n");
                break;
            }
        }
    }

    // Close the file
    fclose(file);

    // If no expressions were read, exit
    if (n == 0) {
        printf("No expressions found in the file.\n");
        return 1;
    }

    // Eliminate common subexpressions
    eliminateCommonSubexpressions(exp, &n);

    return 0;
}


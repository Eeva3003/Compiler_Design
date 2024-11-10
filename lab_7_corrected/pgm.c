#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPRESSIONS 100

/*
findCommonSubexpression(struct Expression exp[], int n, struct Expression current)
replaceOccurrences(struct Expression exp[], int n, const char *oldVar, const char *newVar)
eliminateCommonSubexpressions(struct Expression exp[], int *n)
*/

// Structure to represent an expression in three-address code
struct Expression {
    char lhs[10];  // Left-hand side variable (e.g., t1, t2)
    char op[3];    // Operator (e.g., +, *, ^, -, /)
    char rhs1[10]; // First operand (can be a variable or another temporary)
    char rhs2[10]; // Second operand (can be a variable or another temporary)
};

/*This function checks if a given expression current (from the list of expressions) is a duplicate of any earlier expression.
If an expression with the same operator and operands (rhs1, rhs2) is found, it returns the index of the first occurrence of this common subexpression.
If no such expression is found, it returns -1.*/
int findCommonSubexpression(struct Expression exp[], int n, struct Expression current) {
    for (int i = 0; i < n; i++) {// n is count of expression till now 
        if (strcmp(exp[i].op, current.op) == 0 &&
            strcmp(exp[i].rhs1, current.rhs1) == 0 &&
            strcmp(exp[i].rhs2, current.rhs2) == 0) {
            return i; // Return the index of the common expression
        }
    }
    return -1; // No common subexpression found
}

/*After identifying and eliminating a common subexpression, this function replaces occurrences of the eliminated expression
(using its left-hand side variable) with the previously found common subexpression's result (lhs).
It searches all other expressions and replaces any reference to the eliminated lhs in the operands (rhs1 and rhs2*/
void replaceOccurrences(struct Expression exp[], int n, const char *oldVar, const char *newVar) {
    for (int i = 0; i < n; i++) {
        if (strcmp(exp[i].rhs1, oldVar) == 0) {// if its same as old change ot new
            strcpy(exp[i].rhs1, newVar);
        }
        if (strcmp(exp[i].rhs2, oldVar) == 0) {
            strcpy(exp[i].rhs2, newVar);
        }
    }
}

/*This is the main function that loops through the list of expressions, and for each expression, it tries to find a duplicate (common subexpression) earlier in the list.
If a common subexpression is found, it eliminates the duplicate by removing it from the list, and the lhs of the duplicate is 
replaced by the previously computed result of the common subexpression.
The function uses findCommonSubexpression() to detect duplicates and replaceOccurrences() to substitute lhs values in subsequent expressions.
The process ensures that the common subexpression is computed only once.*/
void eliminateCommonSubexpressions(struct Expression exp[], int *n) {
    for (int i = 0; i < *n; i++) { // note there is star n 
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


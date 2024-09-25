#include <stdio.h>
#include <string.h>

#define MAX_QUADS 100

// Define structure to hold quadruples
typedef struct {
    char op[3];  // Operator
    char o1[5];  // Operand 1
    char o2[5];  // Operand 2
    char res[5]; // Result
} Quadruple;

// Function to check if a common subexpression exists
int is_common_subexpression(Quadruple q[], int index, char res[]) {
    for (int i = 0; i < index; i++) {
        // Check if the current operation and operands match any previous quadruple
        if (strcmp(q[i].op, q[index].op) == 0 && strcmp(q[i].o1, q[index].o1) == 0 && strcmp(q[i].o2, q[index].o2) == 0) {
            strcpy(res, q[i].res);  // Copy the result of the common subexpression
            return 1;  // Found a common subexpression
        }
    }
    return 0;  // No common subexpression found
}

// Function to replace all occurrences of a redundant result in subsequent quadruples
void replace_redundant_result(Quadruple q[], int n, const char *old_res, const char *new_res) {
    for (int i = 0; i < n; i++) {
        if (strcmp(q[i].o1, old_res) == 0) {
            strcpy(q[i].o1, new_res);  // Replace operand1
        }
        if (strcmp(q[i].o2, old_res) == 0) {
            strcpy(q[i].o2, new_res);  // Replace operand2
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;

    // Open input file for reading
    inputFile = fopen("quadraple.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Open output file for writing
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        fclose(inputFile);
        return 1;
    }

    Quadruple q[MAX_QUADS];
    int n = 0;

    // Read the quadruples from the input file
    char header[100];
    fgets(header, sizeof(header), inputFile);  // Read and skip the first line (header)

    // Reading the quadruple tuples from the file
    while (fscanf(inputFile, "%s %s %s %s", q[n].op, q[n].o1, q[n].o2, q[n].res) == 4) {
        n++;
    }

    fclose(inputFile);

    // Perform common subexpression elimination
    Quadruple result[MAX_QUADS];
    int result_count = 0;

    for (int i = 0; i < n; i++) {
        char common_res[5];
        if (is_common_subexpression(q, i, common_res)) {
            // If a common subexpression is found, replace its result in the quadruples
            replace_redundant_result(q, n, q[i].res, common_res);
        } else {
            // Add the current quadruple to the result array
            result[result_count++] = q[i];
        }
    }

    // Write the optimized quadruples to output file (single header)
    fprintf(outputFile, "OP\tO1\tO2\tRES\n");  // Print the header once
    for (int i = 0; i < result_count; i++) {
        fprintf(outputFile, "%s\t%s\t%s\t%s\n", result[i].op, result[i].o1, result[i].o2, result[i].res);
    }

    fclose(outputFile);

    printf("Common subexpression elimination completed. Optimized output written to 'output.txt'.\n");

    return 0;
}


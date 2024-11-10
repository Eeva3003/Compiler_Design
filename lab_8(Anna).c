#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*
int findVariable(char* name)
void addConstant(char* name, float value)
float evaluateExpression(float left, char operator, float right)
int parseAssignment(char* line, char* varName, float* result)
void propagateConstants(char* line)
void parseLine(char* line)
*/
#define MAX_VARIABLES 100
#define MAX_LINE_LENGTH 256

// Structure to store variables and their constant values
typedef struct {
    char name[20];
    float value;
    int isConstant;
} Variable;

Variable variables[MAX_VARIABLES];
int variableCount = 0;

// Searches for a variable by name and returns its index in the variables array or -1 if not found.
int findVariable(char* name) {
    for (int i = 0; i < variableCount; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Adds a new variable as a constant or updates an existing variable with a new constant value.

void addConstant(char* name, float value) {
    int index = findVariable(name);
    if (index == -1) {
        strcpy(variables[variableCount].name, name);
        variables[variableCount].value = value;
        variables[variableCount].isConstant = 1;/*isConstant is set to 1 (true) when a variable is identified as a constant, and it stays as 0 (false) for non-constant variables.*/
        variableCount++;
    } else {
        variables[index].value = value;
        variables[index].isConstant = 1;
    }
}

// Function to evaluate basic expressions (supports +, -, *, /)
float evaluateExpression(float left, char operator, float right) {
    switch (operator) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return right != 0 ? left / right : 0;  // Check for divide-by-zero
        default: return 0;
    }
}

// Function to parse and evaluate assignments like 'pi = 20 / 5'
// Parses assignment statements in the format float var = expr; where expr is a simple binary operation (e.g., 20 / 5).
//If an assignment line follows this format, it returns the computed result in *result and sets varName to the variable name.
int parseAssignment(char* line, char* varName, float* result) {
    int left, right;
    char operator;

    if (sscanf(line, " float %s = %d %c %d ;", varName, &left, &operator, &right) == 4) {
        *result = evaluateExpression((float)left, operator, (float)right);
        return 1;
    }
    return 0;
}

//Scans a line of code, finds occurrences of known constants, and replaces them with their constant values.
void propagateConstants(char* line) {
    for (int i = 0; i < variableCount; i++) {
        if (variables[i].isConstant) {
            char varName[20];
            sprintf(varName, "%s", variables[i].name);

            char constValue[20];
            sprintf(constValue, "%.2f", variables[i].value);
            
            char *pos = strstr(line, varName);
            while (pos != NULL) {
                strncpy(pos, constValue, strlen(constValue));
                if (strlen(varName) > strlen(constValue)) {
                    memmove(pos + strlen(constValue), pos + strlen(varName), strlen(pos + strlen(varName)) + 1);
                }
                pos = strstr(line, varName); // Check for other occurrences
            }
        }
    }
}

// Parses each line of code to determine if it defines a constant. 
//If so, it evaluates the expression, stores the result as a constant, and rewrites the line with the constant value. Otherwise, it performs constant propagation.
void parseLine(char* line) {
    char varName[20];
    float result;

    // Check if line defines a constant expression
    if (parseAssignment(line, varName, &result)) {
        addConstant(varName, result);
        
        // Rewrite line with constant value
        sprintf(line, "float %s = %.2f;\n", varName, result);
    } else {
        propagateConstants(line);
    }
}


//Opens a file named "cd6result.txt", reads each line, and prints the original code.
//Then, it rewinds the file pointer to re-read the file and applies constant propagation on each line before printing the transformed code.
int main() {
    FILE *file = fopen("cd6result.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    printf("Original Code:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    rewind(file);  // Reset file pointer to beginning

    printf("\nAfter Constant Propagation:\n");
    while (fgets(line, sizeof(line), file)) {
        parseLine(line);/*starts with -parseline whichif( first  checks for -parse assignment(which -evaluates expression) if found then
        -addconstant(which checks for -findvariable)) else -propogate constants*/
        printf("%s", line);
    }

    fclose(file);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[100], post[100], stack[100], queue[100];
int top = -1, j = 0;

// Function to check precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    } else {
        return 0;
    }
}

// Function to convert infix to postfix notation
void postfix() {
    int i = 0;
    top = -1;  // Reset stack
    j = 0;     // Reset postfix index

    while (s[i] != '\0') {
        if (s[i] == '(') {
            stack[++top] = s[i];
        } else if (isalpha(s[i])) {
            post[j++] = s[i];
        } else if (precedence(s[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(s[i])) {
                post[j++] = stack[top--];
            }
            stack[++top] = s[i];
        } else if (s[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                post[j++] = stack[top--];
            }
            top--;  // Remove '(' from stack
        }
        i++;
    }
    while (top != -1) {
        post[j++] = stack[top--];
    }
    post[j] = '\0';  // Null-terminate the postfix expression
}

// Function to process the postfix expression and generate three-address, quadruple, and triple code
void processExpression(FILE* fp, FILE* fp1, FILE* fp2) {
    int i = 0;
    char ind = '1';  // Temporary variable index
    int front = -1;  // Queue front pointer, reset for each expression

    while (post[i] != '\0') {
        if (precedence(post[i])) {  // Operator
            char a = queue[front--];  // Pop operands from queue
            char b = queue[front--];
            fprintf(fp, "t%c = %c %c %c\n", ind, b, post[i], a);
            fprintf(fp1, "%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
            fprintf(fp2, "%c\t%c\t%c\t%c\n", ind, post[i], b, a);

            queue[++front] = ind++;  // Push result back onto the queue
        } else {
            queue[++front] = post[i];  // Operand: push to the queue
        }
        i++;
    }
}

void main() {
    FILE *fp, *fp1, *fp2, *fp3;

    // Open files
    fp = fopen("3addr.txt", "w");
    fp1 = fopen("quadraple.txt", "w");
    fp2 = fopen("triple.txt", "w");
    fp3 = fopen("input.txt", "r");

    if (fp == NULL || fp1 == NULL || fp2 == NULL || fp3 == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Write headers to the output files
    fprintf(fp, "Three Address\n");
    fprintf(fp1, "Quadruple\nOP\tO1\tO2\tRES\n");
    fprintf(fp2, "Triple\nIN\tOP\tO1\tO2\n");

    // Read each infix expression from input.txt
    while (fgets(s, sizeof(s), fp3)) {  // Read entire lines (expressions)
        s[strcspn(s, "\n")] = '\0';  // Remove newline character
        printf("Infix : %s\n", s);
        
        // Convert to postfix
        postfix();
        printf("Postfix : %s\n", post);
        
        // Process the postfix expression and generate code
        processExpression(fp, fp1, fp2);
    }

    // Close the files
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

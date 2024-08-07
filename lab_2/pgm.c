#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int priority(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}

int isgreater(char op1, char op2) {
    if (priority(op1) >= priority(op2))
        return 1;
    else
        return 0;
}

int main() {
    char s[100];
    printf("Enter input string: ");
    scanf("%[^\n]s", s);
    
    char stack[100], buffer[100], prev = 'x';
    int indx = 0, top = -1;
    
    printf("STACK\t\tInput\t\tAction");
    printf("\n$\t\t%s$\t\tshift", s);
    while (1) {
        memset(buffer, 0, 100); 
        int flag = 0;
        
        if (isalnum(stack[top]) && stack[top] != 'E') {
            strcpy(buffer, "reduce E->id");
            stack[top] = 'E';
        }
        else if (isalnum(stack[top]) && isalnum(s[indx])){
        	printf("\nMissing operator\n");
          break;}
         else if (indx == strlen(s) && (stack[top] == '+' || stack[top] == '-' || stack[top] == '*' || stack[top] == '/')) {
            break;}
          
        else if (strlen(s) == indx || (top > 1 && !isalnum(s[indx]) && isgreater(prev, s[indx]) == 1)) {
            flag = 1;
            char exp[4];
            exp[0] = stack[top-2]; exp[1] = stack[top-1]; exp[2] = stack[top]; exp[3] = '\0';
            if (strcmp(exp, "E+E") == 0) {
                stack[top] = '\0'; stack[top-1] = '\0';
                top = top - 2;
                strcpy(buffer, "reduce E->E+E ");
            } else if (strcmp(exp, "E-E") == 0) {
                stack[top] = '\0'; stack[top-1] = '\0';
                top = top - 2;
                strcpy(buffer, "reduce E->E-E ");
            } else if (strcmp(exp, "E*E") == 0) {
                stack[top] = '\0'; stack[top-1] = '\0';
                top = top - 2;
                strcpy(buffer, "reduce E->E*E ");
            } else if (strcmp(exp, "E/E") == 0) {
                stack[top] = '\0'; stack[top-1] = '\0';
                top = top - 2;
                strcpy(buffer, "reduce E->E/E ");
              } else if (strcmp(exp, "E^E") == 0) {
                stack[top] = '\0'; stack[top-1] = '\0';
                top = top - 2;
                strcpy(buffer, "reduce E->E^E ");
            } else {
                flag = 0;
            }
            
        } else if (flag == 0) {
            if (indx != strlen(s)) {
                stack[++top] = s[indx++];
                strcpy(buffer, "shift");
                if (!isalnum(stack[top]))
                    prev = stack[top];
            } else {
                break;
            }
        }
        
        printf("\n$%s\t\t", stack);
        for (int j = indx; j < strlen(s); j++)
            printf("%c", s[j]);
        printf("$\t\t%s  ", buffer);
        
        if (stack[top] == 'E' && top == 0 && indx == strlen(s)) {
            printf("\n\nINPUT ACCEPTED\n\n");
            exit(0);
        }
    }
    printf("\n\nINPUT REJECTED\n\n");
    return 0;
}
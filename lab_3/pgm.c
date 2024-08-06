#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i, err;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        i++;
        T();
        Eprime();
    } else if (input[i] == '-') {
        i++;
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        i++;
        F();
        Tprime();
    } else if (input[i] == '/') {
        i++;
        F();
        Tprime();
    }
}

void F() {
    if (isalnum(input[i])) {
        i++;
    } else if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')') {
            i++;
        } else {
            err = 1;
        }
    } else {
        err = 1;
    }
}

int main() {
    i = 0;
    err = 0;
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);
    
    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';
    
    E();
    if (strlen(input) == i && err == 0) {
        printf("%s is accepted\n", input);
    } else {
        printf("%s is rejected\n", input);
    }
    
    return 0;
}


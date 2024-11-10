//:Construct a recursive descent parser for an expression according to the grammar below.
/*
E → TE’ 
E’ → +TE’- TE’/ε 
T → FT’ 
T’ → *FT’/ /FT’/ ε
F → (E) / id
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];//declaring input array globally is very important
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
//final function where the recursive parser concludes
void F() {
    if (isalnum(input[i])) {// if an alphanumeric -- tht is identifier , then incremane to next 
        i++;
    } else if (input[i] == '(') { //or it might be a open paranthesis which again calls the initial e() function
        i++;
        E();
        if (input[i] == ')') { //after which if closing bracket is encountered continue i++ else print error 
            i++;
        } else {
            err = 1;
        }
    } else {// else again error
        err = 1;
    }
}

//main function just takes input , add the '\0 ' and calls the first E() fucntion
//it then checks if i is the last element of input and err is 0 
// if yes then accepted else false
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


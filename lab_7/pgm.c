#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[100], post[100], stack[100], queue[100];
int top = -1, j = 0, front = -1;

struct Expression {
    char op;
    char arg1;
    char arg2;
    char result;
};

struct Expression exprTable[100];
int exprCount = 0;

int precedence(char c){
    if(c == '+' || c == '-'){
        return 1;
    }
    else if(c == '*' || c == '/'){
        return 2;
    }
    else if(c == '^'){
        return 3;
    }
    else{
        return 0;
    }
}

void postfix(){
    int n = strlen(s), i = 0;
    while(s[i] != '\0'){
        if(s[i] == '('){
            top++;
            stack[top] = s[i];
        }
        else if(isalpha(s[i])){
            post[j++] = s[i];
        }
        else if(precedence(s[i])){
            while(precedence(stack[top]) >= precedence(s[i])){
                post[j++] = stack[top--];
            }
            top++;
            stack[top] = s[i];
        }
        else if(s[i] == ')'){
            while(stack[top] != '('){
                post[j++] = stack[top--];
            }
            top--;
        }
        i++;
    }
    while(top!=-1){
        post[j++] = stack[top--];
    }
    post[j] = '\0';
}

int isCommonSubexpression(char op, char arg1, char arg2, char* result){
    for(int i = 0; i < exprCount; i++){
        if(exprTable[i].op == op && exprTable[i].arg1 == arg1 && exprTable[i].arg2 == arg2){
            *result = exprTable[i].result;
            return 1;
        }
    }
    return 0;
}

void addExpression(char op, char arg1, char arg2, char result){
    exprTable[exprCount].op = op;
    exprTable[exprCount].arg1 = arg1;
    exprTable[exprCount].arg2 = arg2;
    exprTable[exprCount].result = result;
    exprCount++;
}

void main(){
    int i = 0;
    char ind = '1';
    
    FILE *fp,*fp1,*fp2,*fp3;
    fp = fopen( "3addr.txt","w");
    fp1 = fopen( "quadraple.txt","w");
    fp2 = fopen( "triple.txt","w");
    fprintf(fp,"Three Address\n");
    fprintf(fp1,"Quadruple\nOP\tO1\tO2\tRES\n");
    fprintf(fp2,"Triple\nIN\tOP\tO1\tO2\n");
    fp3=fopen( "input.txt","r");

    while((fscanf(fp3,"%s",s)) != EOF){
        postfix();
        printf("Infix : %s \nPostfix : %s\n", s, post);
        i = 0;
        while(post[i] != '\0'){
            if(precedence(post[i])){
                char a = queue[front--];
                char b = queue[front--];
                char res;
                
                if(isCommonSubexpression(post[i], b, a, &res)){
                    front++;
                    queue[front] = res;
                }
                else{
                    if(isdigit(a) && isdigit(b)){
                        fprintf(fp,"t%c = t%c %c t%c\n", ind, b, post[i], a);
                        fprintf(fp1,"%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
                    }
                    else if(isdigit(b)){
                        fprintf(fp,"t%c = t%c %c %c\n", ind, b, post[i], a);
                        fprintf(fp1,"%c\tt%c\t%c\tt%c\n", post[i], b, a, ind);
                    }
                    else if(isdigit(a)){
                        fprintf(fp,"t%c = %c %c t%c\n", ind, b, post[i], a);
                        fprintf(fp1,"%c\t%c\tt%c\tt%c\n", post[i], b, a, ind);
                    }
                    else{
                        fprintf(fp,"t%c = %c %c %c\n", ind, b, post[i], a);
                        fprintf(fp1,"%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
                    }
                    fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);
                    
                    // Add the new expression to the table
                    addExpression(post[i], b, a, ind);
                    
                    front++;
                    queue[front] = ind;
                    ind++;
                }
            }
            else{
                front++;
                queue[front] = post[i];
            }
            i++;
        }
    }

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

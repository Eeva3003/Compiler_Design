{\rtf1\ansi\ansicpg1252\cocoartf2813
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include<stdio.h>\
#include<stdlib.h>\
#include<string.h>\
#include <ctype.h>\
\
char s[100], post[100], stack[100], queue[100];\
int top = -1, j = 0, front = -1;\
\
int precedence(char c)\{\
    if(c == '+' || c == '-')\{\
        return 1;\
    \}\
    else if(c == '*' || c == '/')\{\
        return 2;\
    \}\
    else if(c == '^')\{\
        return 3;\
    \}\
    else\{\
        return 0;\
    \}\
\}\
\
void postfix()\{\
    top = -1;\
    j = 0;\
    int n = strlen(s), i = 0;\
    while(s[i] != '\\0')\{\
        if(s[i] == '(')\{\
            stack[++top] = s[i];\
        \}\
        else if(isalpha(s[i]))\{\
            post[j++] = s[i];\
        \}\
        else if(precedence(s[i]))\{\
            while(top != -1 && precedence(stack[top]) >= precedence(s[i]))\{\
                post[j++] = stack[top--];\
            \}\
            stack[++top] = s[i];\
        \}\
        else if(s[i] == ')')\{\
            while(stack[top] != '(')\{\
                post[j++] = stack[top--];\
            \}\
            top--; // pop '('\
        \}\
        i++;\
    \}\
    while(top != -1)\{\
        post[j++] = stack[top--];\
    \}\
    post[j] = '\\0'; // Null terminate the postfix expression\
\}\
\
void main()\{\
    int i = 0;\
    char ind = '1';\
\
    FILE *fp, *fp1, *fp2, *fp3;\
    fp = fopen("3addr.txt", "w");\
    fp1 = fopen("quadraple.txt", "w");\
    fp2 = fopen("triple.txt", "w");\
    fp3 = fopen("input.txt", "r");\
\
    if (!fp || !fp1 || !fp2 || !fp3) \{\
        printf("Error opening file\\n");\
        exit(1);\
    \}\
\
    fprintf(fp, "Three Address\\n");\
    fprintf(fp1, "Quadruple\\nOP\\tO1\\tO2\\tRES\\n");\
    fprintf(fp2, "Triple\\nIN\\tOP\\tO1\\tO2\\n");\
\
    while (fscanf(fp3, "%s", s) != EOF) \{\
        j = 0;  // Reset postfix index for each new expression\
        postfix();\
        printf("Infix: %s\\nPostfix: %s\\n", s, post);\
\
        front = -1; // Reset front for the next expression\
        i = 0;      // Reset index for reading from postfix\
\
        while (post[i] != '\\0') \{\
            if (precedence(post[i])) \{\
                char a = queue[front--];\
                char b = queue[front--];\
                if (isalpha(a) && isalpha(b)) \{\
                    fprintf(fp, "t%c = %c %c %c\\n", ind, b, post[i], a);\
                    fprintf(fp1, "%c\\t%c\\t%c\\tt%c\\n", post[i], b, a, ind);\
                \} else if (isalpha(b)) \{\
                    fprintf(fp, "t%c = %c %c t%c\\n", ind, b, post[i], a);\
                    fprintf(fp1, "%c\\t%c\\tt%c\\tt%c\\n", post[i], b, a, ind);\
                \} else if (isalpha(a)) \{\
                    fprintf(fp, "t%c = t%c %c %c\\n", ind, b, post[i], a);\
                    fprintf(fp1, "%c\\tt%c\\t%c\\tt%c\\n", post[i], b, a, ind);\
                \} else \{\
                    fprintf(fp, "t%c = t%c %c t%c\\n", ind, b, post[i], a);\
                    fprintf(fp1, "%c\\tt%c\\tt%c\\tt%c\\n", post[i], b, a, ind);\
                \}\
                fprintf(fp2, "%c\\t%c\\t%c\\t%c\\n", ind, post[i], b, a);\
                queue[++front] = ind++; // Push result back to the queue\
            \} else \{\
                queue[++front] = post[i]; // Push operand to the queue\
            \}\
            i++;\
        \}\
    \}\
\
    fclose(fp);\
    fclose(fp1);\
    fclose(fp2);\
    fclose(fp3);\
\}\
}
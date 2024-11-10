//declaration and initialisation

%{
#include<stdio.h>
int flag=0;
%}

//token declaration
%token NUMBER

//operator precedence
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

//grammar rules
%%
ArithmeticExpression: E{printf("output:%d\n",$$);return 0;};
//$$ holds the value of the evaluated expression
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|'('E')' {$$=$2;}
| NUMBER {$$=$1;}
;
%%


void main()
{
printf("\nEnter the input:\n");
yyparse();
if(flag==0)
printf("Expression is Valid\n");
}

//yyerror() is a function that gets called when a syntax error occurs during parsing.
void yyerror()
{
printf("Expression is invalid\n");
flag=1;
}









//yacc -d Pg13.y
//lex Pg13.l
//gcc lex.yy.c y.tab.c -w
//./a.out

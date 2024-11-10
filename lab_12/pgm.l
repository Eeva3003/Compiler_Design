%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}
%%
[0-9]+ { yylval=atoi(yytext); return NUMBER;}
[\t] ;
[\n] return 0;
. return yytext[0];
%%
int yywrap()
{
return 1;
}
/*Tokenization:

The Lex scanner reads the input and matches the text according to the rules defined above.
If it matches a number (e.g., 123), it converts it into an integer and returns the token NUMBER with the value of the number.
If it encounters a tab or newline, it just ignores them, but the newline will signal the end of the input.
Any other characters (not matching numbers or whitespace) will be returned individually as tokens using their ASCII value.
Integration with Yacc/Bison:

The yylval variable is used to pass the value of the matched token to the parser (Yacc/Bison).
The parser will then handle the token (NUMBER) and use it in the grammar rules for syntax analysis and processing.*/

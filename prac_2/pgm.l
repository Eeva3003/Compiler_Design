//lex program to count number of words
%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
%}

%%
[ \t\n]+            ; // Ignore whitespace
[a-zA-Z]+          { word_count++; char_count += yyleng; }//yyleng is a special variable in Lex/Flex that holds the length of the matched string (yytext
.                  { char_count++; } // Count any single character

%% 

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    yyin = file; // Set the input stream to the file
    yylex();
    fclose(file);

    printf("Word Count: %d\n", word_count);
    printf("Character Count: %d\n", char_count);
    return 0;
}

//yywrap() is a standard function used in Flex to indicate that the input stream has been fully processed. When Flex finishes reading the input, yywrap() is called.

int yywrap() {
    return 1;
}





//Normal function 
%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
%}

%%

[ \t\n]+            ; // Ignore whitespace
[a-zA-Z]+           { word_count++; char_count += yyleng; } // Count words and characters
.                   { char_count++; } // Count any single character

%% 

int main() {
    printf("Enter text (Ctrl+D to end input):\n");
    yylex(); // Directly process standard input

    printf("Word Count: %d\n", word_count);
    printf("Character Count: %d\n", char_count);
    return 0;
}

// The yywrap() function tells Flex that the input has ended
int yywrap() {
    return 1;
}


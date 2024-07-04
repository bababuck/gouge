%{
#include<stdio.h>

int yylex(void);
void yyerror(const char *s);

%}

%token SYMBOL ASSIGN

%start function
%%

function
    : declaration SYMBOL '(' function_declaration_inputs ')' '{' expressions '}' { printf("FUNCTION\n"); }
    ;

function_declaration_inputs
    : declaration
    | function_declaration_inputs ',' declaration
    ;

declaration
    : SYMBOL SYMBOL

expressions
    : expression
    | expressions expression
    ;

expression
    : SYMBOL ASSIGN SYMBOL ';'
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}

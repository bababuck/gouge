%{
#include<stdio.h>
#include "declaration.h"

int yylex(void);
void yyerror(const char *s);

%}

%token SYMBOL ASSIGN

%start function

%type <declaration> declaration
%type <str> SYMBOL
%type <expression> expression
%type <expressions> expressions

%union {
    declaration_t *declaration;
    char *str;
    expression_t *expression;
    expression_t **expressions;
}
%%

function
    : declaration SYMBOL '(' function_declaration_inputs ')' '{' expressions '}' {
        function_t *function = new_function($2, $1, $4);
        free($2);
        free($1);
        free($4);
        evaluate_function_expressions(function, $7);
        printf("FUNCTION\n");
    }
    ;

function_declaration_inputs
    : declaration { $$ = add_wires(NULL, $1); }
    | function_declaration_inputs ',' declaration { $$ = add_wires($1, $3); }
    ;

declaration
    : SYMBOL SYMBOL { $$ = new_wire($1, $2); }

expressions
    : expression { $$ = make_expressions(1, &($1)); }
    | expressions expression { $$ = add_expression($1, $2); }
    ;

expression
    : SYMBOL ASSIGN SYMBOL ';' { $$ = make_expression($1, '=', $3); }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}

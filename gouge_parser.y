%{
#include<stdio.h>
#include "types.h"
#include "function.h"

int yylex(void);
void yyerror(const char *s);

%}

%token SYMBOL ASSIGN

%start function

%type <wire> declaration
%type <str> SYMBOL
%type <equation> equation
%type <equations> equations
%type <wires> function_declaration_inputs
%type <function> function

%union {
    void *wire;
    char *str;
    void *equation;
    void *equations;
    void *wires;
    void *function;
}
%%

function
    : declaration SYMBOL '(' function_declaration_inputs ')' '{' equations '}' {
        void *function = new_function($2, $1, $4);
        free($2);
        free($1);
        free($4);
        evaluate_function_equations(function, $7);
        $$ = function;
        printf("FUNCTION\n");
    }
    ;

function_declaration_inputs
    : declaration { $$ = add_wires(NULL, $1); }
    | function_declaration_inputs ',' declaration { $$ = add_wires($1, $3); }
    ;

declaration
    : SYMBOL SYMBOL { $$ = new_wire($1, $2); }

equations
    : equation { $$ = add_equation(NULL, &($1)); }
    | equations equation { $$ = add_equation($1, $2); }
    ;

equation
    : SYMBOL ASSIGN SYMBOL ';' { $$ = make_equation($1, '=', $3); }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}

%{
#include<stdio.h>
#include "object.h"
#include "types.h"
#include "function.h"

int yylex(void);
void yyerror(const char *s);

%}

%token SYMBOL ASSIGN IF

%start function

%type <wire> declaration
%type <str> SYMBOL
%type <equation> equation
%type <equations> equations
%type <wires> function_declaration_inputs
%type <function> function_declaration
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
    : function_declaration '{' equations '}' {
        evaluate_function_equations($1, $3);
        printf("FUNCTION\n");
        exit_context();
    }
    ;

function_declaration
    : declaration SYMBOL '(' function_declaration_inputs ')' {
        new_context();
        void *outputs = add_wires(NULL, $1);
        void *function = new_function($2, outputs, $4);
        free($1);
        $$ = function;
    }
    ;

function_declaration_inputs
    : declaration { $$ = add_wires(NULL, $1); }
    | function_declaration_inputs ',' declaration { $$ = add_wires($1, $3); }
    ;

declaration
    : SYMBOL SYMBOL { $$ = new_wire($1, $2); }
    ;

wire_declaration
    : declaration ';' { register_object($1);}
    ;

equations
    : equation { $$ = add_equation(NULL, &($1)); }
    | wire_declaration { $$ = NULL; }
    | equations equation { $$ = add_equation($1, $2); }
    | equations wire_declaration { $$ = $1; }
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

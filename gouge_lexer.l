L   [a-zA-Z_]
A   [a-zA-Z_0-9]
WS  [ \t\v\n\f]

%{
#include <stdio.h>
#include "declaration.h"
#include "y.tab.h"
%}

%%

"="                          { return ASSIGN; }
","					         { return ','; }
"("                          { return '('; }
")"                          { return ')'; }
";"                          { return ';'; }
"{"                          { return '{'; }
"}"                          { return '}'; }

{L}{A}*                      { yylval.str=strdup(yytext); return SYMBOL; }


{WS}+                        { /* whitespace separates tokens */ }
.                            { /* discard bad characters */ }

%%

int yywrap(void)             /* called at end of input */
{
    return 1;                /* terminate now */
}

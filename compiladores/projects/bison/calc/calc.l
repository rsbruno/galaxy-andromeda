%{
#include "calc.h"
#include <stdlib.h>
void yyerror(char *);
%}

%%
[0-9]+  { yylval = atoi(yytext);return NUM;}
"+"     return MAIS;
"-"     return MENOS;
"*"     return VEZES;
"/"     return DIVIDE;
\n      return ENTER;
"("     return ABRE;
")"     return FECHA;

[ \t]+  ;
.       yyerror("simbolo desconhecido");
%%

int yywrap(void){return 1;}

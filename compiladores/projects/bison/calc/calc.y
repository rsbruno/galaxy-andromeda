%{
#include "lexico.c"
%}

%token NUM
%token ENTER
%token MAIS
%token MENOS
%token ABRE
%token FECHA
%token VEZES
%token DIVIDE

%start linha

%left MAIS MENOS
%left VEZES DIVIDE

%%
linha : linha expr ENTER        {printf("resultado =  %d\n", $2);}
        |
        ;
expr :  NUM                     {$$ = $1;}
        |expr MAIS expr         {$$ = $1 + $3;}
        |expr MENOS expr        {$$ = $1 - $3;}
        |expr VEZES expr        {$$ = $1 * $3;}
        |expr DIVIDE expr       {$$ = $1 / $3;}
        |ABRE expr FECHA        {$$ = $2;}
        ;
%%

void yyerror(char *s){
        printf("Erro: %s\n\n", s);
        exit(10);
}

int main(void){
        yyparse();
}
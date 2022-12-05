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
linha : linha comando ENTER   
        |
        ;

comando : expr                  {}
        | VAR RECEBE expr       {printf("\tARZG\t%d\n", $1)}
        ;

expr :  NUM                     {printf("\tCRCT\t%d\n", $1)}
        |VAR                    {printf("\tCRVG\t%d\n", $1)}
        |expr MAIS expr         {printf("\tSOMA\n")}
        |expr MENOS expr        {printf("\tSUBT\n")}
        |expr VEZES expr        {printf("\tVEZES\n")}
        |expr DIVIDE expr       {printf("\tDIVI\n")}
        |ABRE expr FECHA        {}
        ;
%%

void yyerror(char *s){
        printf("Erro: %s\n\n", s);
        exit(10);
}

int main(void){
        yyparse();
}
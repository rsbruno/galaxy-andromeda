%{
#include <stdio.h>
#include <stdlib.h>
#include "lexico.c"

void erro(char *);
int yyerror(char *);
%}

%start programa

%token T_PROGRAMA
%token T_INICIO 
%token T_FIM 
%token T_LEIA 
%token T_ESCREVA 
%token T_SE 
%token T_ENTAO 
%token T_SENAO 
%token T_FIMSE 
%token T_ENQTO 
%token T_FACA 
%token T_FIMENQTO 
%token T_INTEIRO
%token T_LOGICO
%token T_MAIS 
%token T_MENOS 
%token T_VEZES 
%token T_DIV 
%token T_E
%token T_OU
%token T_NAO
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_ATRIB
%token T_ABRE
%token T_FECHA
%token T_V
%token T_F
%token T_IDENTIF
%token T_NUM
%token T_REPITA
%token T_ATE
%token T_FIMREPITA

%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV

%%

programa
    : cabecalho variaveis T_INICIO lista_comandos T_FIM
    ;

cabecalho
    : T_PROGRAMA T_IDENTIF
    ;

variaveis   
    :
    | declaracao_variaveis
    ;

declaracao_variaveis
    : tipo lista_variaveis declaracao_variaveis
    | tipo lista_variaveis
    ;

tipo
    : T_INTEIRO
    | T_LOGICO
    ;

lista_variaveis
    : T_IDENTIF lista_variaveis
    | T_IDENTIF
    ;

lista_comandos
    :
    | comando lista_comandos
    ;

comando
    : leitura
    | escrita
    | repeticao
    | selecao
    | atribuicao
    ;

leitura
    : T_LEIA T_IDENTIF
    ;

escrita
    : T_ESCREVA expr
    ;
    
repeticao
    : T_ENQTO expr T_FACA lista_comandos T_FIMENQTO
    | T_REPITA lista_comandos T_ATE expr T_FIMREPITA
    ;

selecao
    : T_SE expr T_ENTAO lista_comandos T_SENAO lista_comandos T_FIMSE
    ;

atribuicao
    : T_IDENTIF T_ATRIB expr
    ;

expr
    : expr T_VEZES expr
    | expr T_DIV expr
    | expr T_MAIS expr
    | expr T_MENOS expr
    | expr T_MAIOR expr
    | expr T_MENOR expr
    | expr T_IGUAL expr
    | expr T_E expr
    | expr T_OU expr
    | termo
    ;

termo 
    : T_IDENTIF
    | T_NUM
    | T_V
    | T_F
    | T_NAO termo
    | T_ABRE expr T_FECHA
    ;
     
%%

void erro(char *s){
    printf("ERRO: %s\n\n",s);
    exit(0);
}

int yyerror(char *s){
    erro(s);
}

int main(){
    if(!yyparse())
        puts("programa ok!");
}
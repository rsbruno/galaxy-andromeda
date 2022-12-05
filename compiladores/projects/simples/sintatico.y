%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.c"
#include "struct.c"

void erro(char *);
int yyerror(char *);
int conta =0, rotulo=0;
char tipo;
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
    : cabecalho variaveis
        { 
            mostra_tabela();
            fprintf(yyout,"\tAMEM\t%d\n",conta);
            empilha(conta);
        }
      T_INICIO lista_comandos T_FIM
        {fprintf(yyout,"\tDMEM\t%d\n", desempilha());}
        {fprintf(yyout,"\tFIMP\n");}
    ;

cabecalho
    : T_PROGRAMA T_IDENTIF
        {fprintf(yyout,"\tINPP\n");}
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
    : T_INTEIRO {tipo = 'i';}
    | T_LOGICO  {tipo = 'l';}
    ;

lista_variaveis
    : lista_variaveis T_IDENTIF
        {
            strcpy(elem_tab.id,atomo);
            elem_tab.endereco = conta++;
            elem_tab.tipo = tipo;
            insere_simbolo(elem_tab);
        }
    | T_IDENTIF
        {
            strcpy(elem_tab.id,atomo);
            elem_tab.endereco = conta++;
            elem_tab.tipo = tipo;
            insere_simbolo(elem_tab);
        }
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
        {
            fprintf(yyout,"\tLEIA\n");
            
            int pos = busca_simbolo(atomo);
            char menssagem[256];
            snprintf(menssagem, sizeof(menssagem), "variavel %s, nao declarada!\n", atomo);
            if(pos == -1)
                erro(menssagem);
            
            fprintf(yyout,"\tARZG\t%d\n", TabSimb[pos].endereco);
        }
    ;

escrita
    : T_ESCREVA expr
        {
            desempilha();
            fprintf(yyout,"\tESCR\n");
        }
    ;
    
repeticao
    : T_ENQTO 
        {
            fprintf(yyout,"L%d\tNADA\n", ++rotulo);
            empilha(rotulo);
        }
      expr T_FACA 
        {
            char termo = desempilha();
            if(termo != 'l')
                erro("Incompatibilidade de tipos\n");
            fprintf(yyout,"\tDSVF\tL%d\n", ++rotulo);
            empilha(rotulo);
        }
      lista_comandos T_FIMENQTO
        {
            int saida = desempilha();
            int entrada = desempilha();
            fprintf(yyout,"\tDSVS\tL%d\n", entrada);
            fprintf(yyout,"L%d\tNADA\n", saida);
        }

    | T_REPITA 
        {
            fprintf(yyout,"L%d\tNADA\n", ++rotulo);
            empilha(rotulo);
        }
        lista_comandos T_ATE expr 
        {
            char termo = desempilha();
            if(termo != 'l')
                erro("Incompatibilidade de tipos\n");
            int saida = desempilha();
            fprintf(yyout,"\tDSVF\tL%d\n", ++rotulo);
            fprintf(yyout,"\tDSVS\tL%d\n", saida);
            empilha(rotulo);
        } 
        T_FIMREPITA
        {
            int saida = desempilha();
            fprintf(yyout,"L%d\tNADA\n", saida);
        }
    ;

selecao
    : T_SE expr T_ENTAO
         {
            char termo = desempilha();
            if(termo != 'l')
                erro("Incompatibilidade de tipos\n");
            fprintf(yyout,"\tDSVF\tL%d\n",++rotulo);
            empilha(rotulo); // empilha o senão
         }
      lista_comandos T_SENAO
         {
            int senao = desempilha(); // desepilha o senao
            fprintf(yyout,"\tDSVS\tL%d\n", ++rotulo);
            empilha(rotulo); // epilha o se
            fprintf(yyout,"L%d\tNADA\n", senao);
        }
      lista_comandos T_FIMSE
        {
            int se = desempilha(); // desempilha o se que manda pra saida
            fprintf(yyout,"L%d\tNADA\n", se);
        }
    ;

atribuicao
    : T_IDENTIF
        {
            int pos = busca_simbolo(atomo);
            char menssagem[256];
            snprintf(menssagem, sizeof(menssagem), "variavel %s, nao declarada!\n", atomo);
            if(pos == -1)
                erro(menssagem);
            empilha(pos);
        }
     T_ATRIB expr
        {
            char tipo = desempilha();
            int p = desempilha();

            if(tipo != TabSimb[p].tipo)
                erro("Incompatibilidade de tipos\n");
            fprintf(yyout,"\tARZG\t%d\n", TabSimb[p].endereco);
        }
    ;

expr
    : expr T_VEZES expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tMULT\n");
        }
    | expr T_DIV expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tDIVI\n");
        }
    | expr T_MAIS expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tSOMA\n");
        }
    | expr T_MENOS expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tSUBT\n");
        }
    | expr T_MAIOR expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('l');
            fprintf(yyout,"\tCMMA\n");
        }
    | expr T_MENOR expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('l');
            fprintf(yyout,"\tCMME\n");
        }
    | expr T_IGUAL expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'i' || t2 != 'i')
                erro("Incompatibilidade de tipos\n");
            empilha('l');
            fprintf(yyout,"\tCMIG\n");
        }
    | expr T_E expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'l' || t2 != 'l')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tCONJ\n");
        }
    | expr T_OU expr
        {
            char t1 = desempilha();    
            char t2 = desempilha();    
            if(t1 != 'l' || t2 != 'l')
                erro("Incompatibilidade de tipos\n");
            empilha('i');
            fprintf(yyout,"\tDISJ\n");
        }
    | termo
    ;

termo 
    : T_IDENTIF
        {
            int pos = busca_simbolo(atomo);
            char menssagem[256];
            snprintf(menssagem, sizeof(menssagem), "variavel %s, nao declarada!\n", atomo);
            if(pos == -1)
                erro(menssagem);
            fprintf(yyout,"\tCRVG\t%d\n",TabSimb[pos].endereco);
            empilha(TabSimb[pos].tipo);
        }
    | T_NUM
        {
            fprintf(yyout,"\tCRCT\t%s\n", atomo);
            empilha('i');
        }
    | T_V
        {
            fprintf(yyout,"\tCRCT\t1\n");
            empilha('l');
        }
    | T_F
        {
            fprintf(yyout,"\tCRCT\t0\n");
            empilha('l');    
        }
    | T_NAO termo
        {
            char termo = desempilha();
            if(termo != 'l')
                erro("Incompatibilidade de tipos\n");
            empilha('l');
            fprintf(yyout,"\tNEGA\n");}
    | T_ABRE expr T_FECHA
    ;
     
%%

void erro(char *s){
    printf("ERRO na linha %d: %s\n\n",numLinha,s);
    exit(0);
}

int yyerror(char *s){
    erro(s);
}

int main(int argc, char *argv[]){
    char *p, nameIn[100], nameOut[100];

    argv++;
    if(argc < 2){
        puts("\nCompilador Simples");
        puts("\n\tUSO: ./simples <nomefonte>[.simples]\n\n");
        exit(10);
    }

    p = strstr(argv[0], ".simples");
    if(p)*p=0;
    strcpy(nameIn, argv[0]);
    strcat(nameIn, ".simples");
    strcpy(nameOut, argv[0]);
    strcat(nameOut, ".mvs");
    yyin = fopen(nameIn, "rt");
    if(!yyin){
        puts("Programa fonte nao encontrado!\n\n");
        exit(10);
    }

    yyout = fopen(nameOut, "wt");


    if(!yyparse())
        puts("programa ok!");
}
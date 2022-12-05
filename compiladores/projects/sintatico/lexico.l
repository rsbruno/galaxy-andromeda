%{
#include "sintatico.h"
void erro(char *s);
%}

identificador [a-zA-z][a-zA-z0-9]*
numero [0-9]+
espaco [ \t\r]+
novalinha [\n]

%option noyywrap

%x comentario

%%
programa            return T_PROGRAMA;
inicio              return T_INICIO ;
fimprograma         return T_FIM ;
leia                return T_LEIA ;
escreva             return T_ESCREVA ;
se                  return T_SE ;
entao               return T_ENTAO ;
senao               return T_SENAO ;
fimse               return T_FIMSE ;
enquanto            return T_ENQTO ;
faca                return T_FACA ;
fimenquanto         return T_FIMENQTO ;
repita              return T_REPITA;
ate                 return T_ATE;
fimrepita           return T_FIMREPITA;

inteiro             return T_INTEIRO;
logico              return T_LOGICO;

"+"                 return T_MAIS ;
"-"                 return T_MENOS ;
"*"                 return T_VEZES ;
div                 return T_DIV ;

e                   return T_E;
ou                  return T_OU;
nao                 return T_NAO;

">"                 return T_MAIOR;
"<"                 return T_MENOR;
"="                 return T_IGUAL;

"<-"                return T_ATRIB;
"("                 return T_ABRE;
")"                 return T_FECHA;

V                   return T_V;
F                   return T_F;

{identificador}     return T_IDENTIF;
{numero}            return T_NUM;
{espaco}            ;/*sem processamento*/
{novalinha}         ;/*sem processamento*/

"//".*              ;/*sem processamento*/
"/*"                BEGIN(comentario);
<comentario>"*/"    BEGIN(INITIAL);
<comentario>.       ;/*sem processamento*/
<comentario>\n      ;/*sem processamento*/
.                   erro("ERRO LEXICO");
%%
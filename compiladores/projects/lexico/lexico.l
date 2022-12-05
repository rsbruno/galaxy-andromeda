identificador [a-zA-z][a-zA-z0-9]*
numero [0-9]+
espaco [" "\n\t]+
novalinha [\n]

%x comentario
%{
    int nlinha = 0;
%}

%%
programa            printf("reservada   : %s\n",yytext);
inicio              printf("reservada   : %s\n",yytext);
fimprograma         printf("reservada   : %s\n",yytext);
leia                printf("reservada   : %s\n",yytext);
escreva             printf("reservada   : %s\n",yytext);
se                  printf("reservada   : %s\n",yytext);
entao               printf("reservada   : %s\n",yytext);
senao               printf("reservada   : %s\n",yytext);
fimse               printf("reservada   : %s\n",yytext);
enquanto            printf("reservada   : %s\n",yytext);
faca                printf("reservada   : %s\n",yytext);
fimenquanto         printf("reservada   : %s\n",yytext);

inteiro             printf("tipo        : %s\n",yytext);
logico              printf("tipo        : %s\n",yytext);

"+"                 printf("aritmetico  : %s\n",yytext);
"-"                 printf("aritmetico  : %s\n",yytext);
"*"                 printf("aritmetico  : %s\n",yytext);
div                 printf("aritmetico  : %s\n",yytext);

e                   printf("logico      : %s\n",yytext);
ou                  printf("logico      : %s\n",yytext);
nao                 printf("logico      : %s\n",yytext);

">"                 printf("relacional  : %s\n",yytext);
"<"                 printf("relacional  : %s\n",yytext);
"="                 printf("relacional  : %s\n",yytext);

"<-"                printf("atribuicao  : %s\n",yytext);

V                   printf("constante   : %s\n",yytext);
F                   printf("constante   : %s\n",yytext);

{identificador}     printf("identific.  : %s\n",yytext);
{numero}            printf("numero      : %s\n",yytext);
{espaco}            /*sem processamento*/;
{novalinha}         ;

"//".*              ;/*sem processamento*/
"/*"                BEGIN(comentario);
<comentario>"*/"    BEGIN(INITIAL);
<comentario>.       ;/*sem processamento*/
<comentario>\n      nlinha++;
.                   printf("ERRO LEXICO : %s\n",yytext);
%%

int yywrap(void){
    return 1;
}

int main(){
    yylex();
    return 1;
}
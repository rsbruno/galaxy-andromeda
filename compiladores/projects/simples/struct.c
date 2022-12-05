#define TAM_TAB 100
#define TAM_PIL 100

int Pilha[TAM_PIL];
int topo = -1;

struct elem_tab_simbolos
{
    char id[100];
    int endereco;
    char tipo;
} TabSimb[TAM_TAB], elem_tab;
int pos_tab;

void empilha(int valor)
{
    if (topo == TAM_PIL)
        erro("Pilha Cheia!");
    Pilha[++topo] = valor;
}

int desempilha()
{
    if (topo == -1)
        erro("Pilha Vazia!");
    return Pilha[topo--];
}

int busca_simbolo(char *id)
{
    int i = pos_tab - 1;
    for (; strcmp(TabSimb[i].id, id) && i >= 0; i--)
        ;
    return i;
}

void insere_simbolo(struct elem_tab_simbolos elem)
{
    int i;
    if (pos_tab == TAM_TAB)
        erro("Tabela de simbolos cheia!\n");
    i = busca_simbolo(elem.id);
    if (i != -1)
        erro("Identificador duplicado!\n");
    TabSimb[pos_tab++] = elem;
}

void mostra_tabela()
{
    int i;
    puts("Tabela de Simbolos");
    printf("\n\n%3s | %30s  |   %3s | %3s \n", "#", "ID", "END", "TIP");
    for (int i = 0; i < 60; i++)
        printf("-");
    for (int i = 0; i < pos_tab; i++)
        printf("\n%3d | %30s  |   %3d | %2c", i, TabSimb[i].id, TabSimb[i].endereco, TabSimb[i].tipo);
    puts("\n\n");
}

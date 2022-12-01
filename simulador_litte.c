#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct little_
{
    unsigned long int no_eventos;
    double tempo_anterior;
    double soma_areas;
} little;

double aleatorio()
{
    double u = rand() / ((double)RAND_MAX + 1);
    u = 1.0 - u;
    return (u);
}

double minimo(double num1, double num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    return num2;
}

double minimo_entre_tres(double num1, double num2, double num3)
{
    double min = minimo(minimo(num1, num2), num3);
    return min;
}

double maximo(double num1, double num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}

void inicia_little(little *l)
{
    l->no_eventos = 0;
    l->tempo_anterior = 0.0;
    l->soma_areas = 0.0;
}

int main()
{
    double tempo_simulacao = 36000;
    double tempo_decorrido = 0.0;
    double tempo_intervalo = 100.0;
    double intervalo_medio_chegada = 5;
    unsigned int semente = 100000;
    double entrada_ocupacao = 99.0; // ocupação em porcentagem
    double tempo_medio_servico = (entrada_ocupacao / 100.0) * intervalo_medio_chegada;

    double chegada;
    double servico;

    double soma_tempo_servico = 0.0;

    unsigned long int fila = 0;
    unsigned long int max_fila = 0;

    little e_n;
    little e_w_chegada;
    little e_w_saida;

    inicia_little(&e_n);
    inicia_little(&e_w_chegada);
    inicia_little(&e_w_saida);

    srand(semente);
    printf("%d \n", semente);

    chegada = (-1.0 / (1.0 / intervalo_medio_chegada)) * log(aleatorio());

    while (tempo_decorrido <= tempo_simulacao)
    {
        tempo_decorrido = !fila ? minimo(chegada, tempo_intervalo) : minimo(chegada, minimo(servico, tempo_intervalo));
        if (tempo_decorrido == tempo_intervalo)
        {
            e_w_chegada.soma_areas +=
                (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;

            e_w_saida.soma_areas +=
                (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;

            double e_n_final = e_n.soma_areas / tempo_decorrido;

            double e_w_final =
                (e_w_chegada.soma_areas - e_w_saida.soma_areas) / e_w_chegada.no_eventos;

            double ocupacao = soma_tempo_servico / maximo(tempo_decorrido, servico);

            double lambda = e_w_chegada.no_eventos / tempo_decorrido;

            double erro_de_litte = e_n_final - lambda * e_w_final;

            printf("%6.0lF %10lF %10lF %10lF %.20lF\n", tempo_intervalo, ocupacao, e_w_final, e_n_final, erro_de_litte);

            tempo_intervalo += 100.0;
            fila = 0;
            max_fila = 0;
            chegada = 0;
            tempo_decorrido = 0.0;
            soma_tempo_servico = 0.0;

            inicia_little(&e_n);
            inicia_little(&e_w_chegada);
            inicia_little(&e_w_saida);
        }
        else if (tempo_decorrido == chegada)
        {
            if (!fila)
            {
                servico = tempo_decorrido + (-1.0 / (1.0 / tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;
            }
            fila++;
            max_fila = fila > max_fila ? fila : max_fila;

            chegada = tempo_decorrido + (-1.0 / (1.0 / intervalo_medio_chegada)) * log(aleatorio());

            e_n.soma_areas +=
                (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos++;
            e_w_chegada.soma_areas +=
                (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
            e_w_chegada.tempo_anterior = tempo_decorrido;
            e_w_chegada.no_eventos++;
        }
        else
        {
            fila--;
            if (fila)
            {
                servico = tempo_decorrido + (-1.0 / (1.0 / tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;
            }
            e_n.soma_areas +=
                (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos--;
            e_w_saida.soma_areas +=
                (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;
            e_w_saida.tempo_anterior = tempo_decorrido;
            e_w_saida.no_eventos++;
        }
    }
    return 0;
}
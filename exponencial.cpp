#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double uniforme()
{
    double u = rand() / ((double)RAND_MAX + 1);
    u = 1.0 - u;

    return (u);
}

double min(double v1, double v2)
{
    if (v1 < v2)
        return v1;
    return v2;
}

int main()
{
    int semente = time(NULL);
    srand(semente);

    double media_chegada;
    printf("Informe o tempo medio entre clientes: ");
    scanf("%lF", &media_chegada);
    media_chegada = 1.0 / media_chegada;

    double media_servico;
    printf("Informe o tempo medio de servico (s): ");
    scanf("%lF", &media_servico);
    media_servico = 1.0 / media_servico;

    double tempo_simulacao;
    printf("Informe o tempo a ser simulado (s): ");
    scanf("%lF", &tempo_simulacao);
    tempo_simulacao = 1.0 / tempo_simulacao;

    double tempo_decorrido = 0; // tempo que já se passou

    double tempo_chegada = (-1.0 / media_chegada) * log(uniforme()); // chegada da primeira instância

    double tempo_saida = 0;

    // unsigned limita a variavel apenas para positivos aumentando o limite
    unsigned long int fila = 0;

    while (tempo_decorrido < tempo_simulacao)
    {
        tempo_decorrido = tempo_saida ? min(tempo_chegada, tempo_saida) : tempo_chegada; // tempo de saída não pode ser zero

        if (tempo_decorrido == tempo_chegada)
        { // chegada de instancia
            if (fila)
                fila++;
            else
                tempo_saida = tempo_decorrido + (-1.0 / media_servico) * log(uniforme());
            tempo_chegada = tempo_decorrido + (-1.0 / media_servico) * log(uniforme());
        }
        else if (tempo_decorrido == tempo_saida)
        { // saída de instancia
            if (fila)
            {
                fila--;
                tempo_saida = tempo_decorrido + (-1.0 / media_servico) * log(uniforme());
            }
            else
            {
                tempo_saida = 0.0; // estando ocioso deve voltar o tempo de saida para o inicio
            }
        }
        else
        {
            printf("Evento inválido!");
            return (1);
        }
    }

    return 0;
}
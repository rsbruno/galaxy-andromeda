/* 
 * File:   main.c
 * Author: Flavio B Gonzaga
 *
 * Created on 08 de Março de 2022.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double aleatorio() {
	double u = rand() / ((double) RAND_MAX + 1);
	//limitando entre (0,1]
	u = 1.0 - u;

	return (u);
}

double minimo(double n1, double n2) {
	if (n1 < n2)
		return n1;
	return n2;
}

int main() {
	/*****************************
	 *  Declaração das variaveis *
	 *****************************/
	/* Gerar numeros pseudoaleatorios
	 * com media igual a 5.
	 * 
	 * Na exponencial, E[X] = 1/l
	 * 
	 * E[X] = 5
	 * 1/l = 5
	 * l = 1/5
	 * l = 0.2
	 * 
	 */

	double parametro_req, parametro_atend,
			tempo_simulacao, tempo_decorrido = 0.0,
			tempo_chegada, tempo_saida, soma_ocupacao = 0.0;

	long int fila = 0;

	printf("Informe o intervalo medio entre requisicoes (segundos): ");
	scanf("%lF", &parametro_req);
	parametro_req = 1.0 / parametro_req; //parametro Exponencial

	printf("Informe o tempo medio de atendimento (segundos): ");
	scanf("%lF", &parametro_atend);
	parametro_atend = 1.0 / parametro_atend; //parametro Exponencial

	printf("Informe o tempo de simulacao (segundos): ");
	scanf("%lF", &tempo_simulacao);

	/***************************
	 *  Iniciando semente      *
	 ***************************/

	int sementeAleat;
	sementeAleat = time(NULL);
	srand(sementeAleat); //inicia o rand

	/************************
	 *Tempo chegada 1a req  *
	 ************************/

	tempo_chegada = (-1.0 / parametro_req) * log(aleatorio());

	/************************
	 *	     Execucao       *
	 ************************/

	long int max_fila = 0;
	while (tempo_decorrido <= tempo_simulacao) {
		if (fila == 0) {
			tempo_decorrido = tempo_chegada;
		} else {
			tempo_decorrido = minimo(tempo_chegada, tempo_saida);
		}

		//printf("tempo_decorrido: %lF\n", tempo_decorrido);
		if (tempo_decorrido == tempo_chegada) {
			//tratando a chegada de requisicao
			//printf("Evento de chegada!\n");
			if (fila == 0) {
				tempo_saida = tempo_decorrido +
						(-1.0 / parametro_atend) * log(aleatorio());
				soma_ocupacao += tempo_saida - tempo_decorrido;
			}
			fila++;
			if (fila > max_fila)
				max_fila = fila;

			tempo_chegada = tempo_decorrido +
					(-1.0 / parametro_req) * log(aleatorio());
			//printf("Tamanho da fila: %d.\n", fila);
			//printf("----------------------------\n");
		} else {
			//tratando a saida de requisicao
			//printf("Evento de saida!\n");
			fila--;
			if (fila > 0) {
				tempo_saida = tempo_decorrido +
						(-1.0 / parametro_atend) * log(aleatorio());
				soma_ocupacao += tempo_saida - tempo_decorrido;

			}
			//printf("Tamanho da fila: %d.\n", fila);
			//printf("----------------------------\n");
		}
	}
	printf("Fim da simulacao. Maior tamanho de fila: %d.\n", max_fila);
	printf("Ocupacao: %lF\n",soma_ocupacao / tempo_decorrido);
	getchar();
	getchar();

	exit(0);
}
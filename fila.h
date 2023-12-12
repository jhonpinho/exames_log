// fila.h
#ifndef FILA_H
#define FILA_H

#include <stdlib.h>

typedef struct No {
  int dado;
  int condicao;
  int instante_tempo;
  int tempo_espera;
  struct No *proximo;
} No;

typedef struct {
  No *inicio;
  No *fim;
  int tamanho;
} Fila;

Fila *inicializarFila();
int filaVazia(Fila *fila);
void enfileirar(Fila *fila, int dado);
int desenfileirar(Fila *fila);
void liberarFila(Fila *fila);
void enfileirarLaudo(Fila *fila, int idPaciente, int condicao,
                     int instanteTempo, int tempoEspera);

#endif

// fila.c
#include "fila.h"
#include <stdio.h>

Fila *inicializarFila() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
  return fila;
}

int filaVazia(Fila *fila) { return (fila->tamanho == 0); }

void enfileirar(Fila *fila, int dado) {
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->dado = dado;
  novoNo->proximo = NULL;

  if (filaVazia(fila)) {
    fila->inicio = novoNo;
    fila->fim = novoNo;
  } else {
    fila->fim->proximo = novoNo;
    fila->fim = novoNo;
  }

  fila->tamanho++;
}

int desenfileirar(Fila *fila) {
  if (filaVazia(fila)) {
    printf("Erro: a fila está vazia.\n");
    exit(EXIT_FAILURE);
  }

  No *noRemovido = fila->inicio;
  int dado = noRemovido->dado;

  fila->inicio = fila->inicio->proximo;
  free(noRemovido);

  fila->tamanho--;

  return dado;
}

void liberarFila(Fila *fila) {
  No *atual = fila->inicio;
  while (atual != NULL) {
    No *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }
  free(fila);
}

void enfileirarLaudo(Fila *fila, int idPaciente, int condicao,
                     int instanteTempo, int tempoEspera) {
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->dado = idPaciente;
  novoNo->condicao = condicao;
  novoNo->instante_tempo = instanteTempo;
  novoNo->tempo_espera = tempoEspera;
  novoNo->proximo = NULL;

  if (filaVazia(fila)) {
    fila->inicio = novoNo;
    fila->fim = novoNo;
  } else {
    fila->fim->proximo = novoNo;
    fila->fim = novoNo;
  }

  fila->tamanho++;
}

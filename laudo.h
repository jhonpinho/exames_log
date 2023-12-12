// laudo.h
#ifndef LAUDO_H
#define LAUDO_H

#include "fila.h"

typedef struct {
  int id_paciente;
  int instante_tempo;
  int condicao;
  int tempo_espera;
} RegistroLaudo;
int gerarCondicaoAleatoria();
void gerarLaudo(Fila *filaExames, Fila *filaLaudo,
                int *radiologistasDisponiveis, int tempo);

#endif

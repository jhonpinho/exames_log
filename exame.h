// exame.h
#ifndef EXAME_H
#define EXAME_H

#include "fila.h"

typedef struct {
  int id_paciente;
  int tempo_exame;
  int instante_tempo;
  int condicao;
} Exame;

void iniciarExame(Fila *filaPacientes, Fila *filaExames, Fila *filaLaudo,
                  int *aparelhosDisponiveis, int tempo);

#endif

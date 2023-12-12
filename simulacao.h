// simulacao.h
#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "fila.h"

void simularChegadaPacientes(Fila *filaPacientes, int *idPaciente, int tempo);
void simularExameRaioX(Fila *filaPacientes, Fila *filaExames, Fila *filaLaudo,
 int *aparelhosDisponiveis, int tempo, int *idPaciente);
void simularLaudos(Fila *filaExames, Fila *filaLaudo,
                   int *radiologistasDisponiveis, int tempo);

int existeMedicoDisponivel();

#endif

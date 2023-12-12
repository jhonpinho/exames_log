// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>

typedef struct {
  char nome[50];
  char cpf[15];
  int idade;
  int id;
} Paciente;

void gerarCpfAleatorio(char *cpf);
Paciente criarNovoPaciente();

#endif

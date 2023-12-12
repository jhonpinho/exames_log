// paciente.c
#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gerarCpfAleatorio(char *cpf) {
  sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000,
          rand() % 1000, rand() % 100);
}

Paciente criarNovoPaciente() {
  Paciente novoPaciente;
  gerarCpfAleatorio(novoPaciente.cpf);
  sprintf(novoPaciente.nome, "Paciente%d", novoPaciente.id);
  novoPaciente.idade = rand() % 100;
  return novoPaciente;
}

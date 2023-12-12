// simulacao.c
#include "simulacao.h"
#include "exame.h"
#include "fila.h"
#include "laudo.h"
#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUMERO_MEDICOS 3

static int medicosOcupados[NUMERO_MEDICOS] = {0};

int existeMedicoDisponivel() {
  for (int i = 0; i < NUMERO_MEDICOS; ++i) {
    if (!medicosOcupados[i]) {
      return 1; // Médico livre encontrado
    }
  }
  return 0; // Nenhum médico livre
}

// simulacao.c
// ...

void simularChegadaPacientes(Fila *filaPacientes, int *idPaciente, int tempo) {
  if (rand() % 100 < 20) {
    enfileirar(filaPacientes, *idPaciente);

    printf("Tempo %d: Chegou um novo paciente. Paciente %d\n", tempo,
           *idPaciente);

    (*idPaciente)++;
  }
}

void simularExameRaioX(Fila *filaPacientes, Fila *filaExames, Fila *filaLaudo,
                       int *aparelhosDisponiveis, int tempo, int *idPaciente) {
  if (!filaVazia(filaPacientes) && *aparelhosDisponiveis > 0) {
    int idPacienteAtual = desenfileirar(filaPacientes);
    int tempoExame = rand() % 6 + 5;

    Exame novoExame;
    novoExame.id_paciente = idPacienteAtual;
    novoExame.tempo_exame = tempoExame;
    novoExame.instante_tempo = tempo;

    enfileirar(filaExames, idPacienteAtual);

    printf("Tempo %d: Iniciando exame para Paciente %d. Tempo estimado: %d\n",
           tempo, idPacienteAtual, tempoExame);

    enfileirarLaudo(filaLaudo, idPacienteAtual, novoExame.instante_tempo, 0, 0);
  }
}

void simularLaudos(Fila *filaExames, Fila *filaLaudo,
                   int *radiologistasDisponiveis, int tempo) {
  if (!filaVazia(filaExames) && *radiologistasDisponiveis > 0) {
    int idPaciente = desenfileirar(filaExames);
    int tempoPreparoLaudo = rand() % 21 + 10;

    RegistroLaudo novoLaudo;
    novoLaudo.id_paciente = idPaciente;
    novoLaudo.condicao =
        rand() % 5; // Ajustado para garantir 5 condições possíveis
    novoLaudo.instante_tempo = tempo + tempoPreparoLaudo;

    // Corrigido para garantir que a condição esteja no intervalo correto
    if (novoLaudo.condicao < 0) {
      novoLaudo.condicao = 0;
    } else if (novoLaudo.condicao > 4) {
      novoLaudo.condicao = 4;
    }

    novoLaudo.tempo_espera = tempo - filaLaudo->inicio->instante_tempo;
    if (novoLaudo.tempo_espera < 0) {
      novoLaudo.tempo_espera = 0;
    }

    printf("Tempo %d: Laudo para Paciente %d concluído em %d unidades de "
           "tempo. Condição: %d.\n",
           tempo + tempoPreparoLaudo, idPaciente, tempoPreparoLaudo,
           novoLaudo.condicao);

    enfileirarLaudo(filaLaudo, idPaciente, novoLaudo.condicao,
                    novoLaudo.instante_tempo, novoLaudo.tempo_espera);
    (*radiologistasDisponiveis)++;
  }

  // Atualiza o tempo de espera apenas para laudos já atendidos pelos
  // radiologistas
  No *atual = filaLaudo->inicio;
  while (atual != NULL && atual->instante_tempo <= tempo) {
    atual->tempo_espera = tempo - atual->instante_tempo;
    if (atual->tempo_espera < 0) {
      atual->tempo_espera = 0;
    }
    atual = atual->proximo;
  }
}

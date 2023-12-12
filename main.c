// main.c

#include "fila.h"
#include "laudo.h"
#include "logging.h"
#include "simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
  srand(time(NULL));

  Logging *logging = create_logging();

  Fila *filaPacientes = inicializarFila(100);
  Fila *filaExames = inicializarFila(100);
  Fila *filaLaudo = inicializarFila(100);

  int idPaciente = 1;
  int aparelhosDisponiveis = 5;
  int radiologistasDisponiveis = 3;

  // Abre o arquivo de log para escrita
  FILE *log_file = fopen("log.txt", "w");
  if (log_file == NULL) {
    perror("Erro ao abrir o arquivo de log");
    exit(EXIT_FAILURE);
  }

  for (int tempo = 1; tempo <= 20; tempo++) {
    // Simulação da chegada de pacientes
    simularChegadaPacientes(filaPacientes, &idPaciente, tempo);

    // Simulação de exames de raio-x
    simularExameRaioX(filaPacientes, filaExames, filaLaudo,
                      &aparelhosDisponiveis, tempo, &idPaciente);

    // Simulação de laudos
    simularLaudos(filaExames, filaLaudo, &radiologistasDisponiveis, tempo);

    // Simulação do sistema de logging para chegada de pacientes
    if (!filaVazia(filaPacientes)) {
      int idNovoPaciente = filaPacientes->inicio->dado;

      char log_info[256];
      snprintf(log_info, sizeof(log_info), "Tempo %d: Paciente %d chegou.",
               tempo, idNovoPaciente);
      write_log(logging, log_info);
      fprintf(log_file, "%s\n", log_info);
    }

    // Simulação do sistema de logging para realização de exames
    if (!filaVazia(filaExames)) {
      int idExame = filaExames->inicio->dado;

      char log_info[256];
      snprintf(log_info, sizeof(log_info),
               "Tempo %d: Exame do Paciente %d realizado.", tempo, idExame);
      write_log(logging, log_info);
      fprintf(log_file, "%s\n", log_info);
    }

    // Imprimir métricas e outras mensagens a cada 10 unidades de tempo
    if (tempo % 10 == 0) {
      printf("\n--- Relatório de Métricas (Tempo %d) ---\n", tempo);
      calcularEMostrarMetricas(filaLaudo, tempo);

      // Adicionar mensagem de log para métricas
      write_log(logging, "Tempo %d: Métricas exibidas.", tempo);
      fprintf(log_file, "Tempo %d: Métricas exibidas.\n", tempo);
    }

    // Sleep para simular passagem do tempo
    sleep(1);
  }

  // Liberar memória
  liberarFila(filaPacientes);
  liberarFila(filaExames);
  liberarFila(filaLaudo);

  // Fechar o arquivo de log
  fclose(log_file);

  // Imprimir logs no arquivo log.txt
  print_logs(logging, "log.txt");

  // Liberar memória do sistema de logging
  free(logging);

  return 0;
}

// laudo.c
#include "laudo.h"
#include "exame.h"
#include <stdio.h>
#include <stdlib.h>
int gerarCondicaoAleatoria() {
    // Gera um número aleatório entre 0 (inclusive) e 1 (exclusivo)
    double probabilidade = (double)rand() / (RAND_MAX + 1);

    // Verifica as probabilidades cumulativas
    if (probabilidade < 0.3) {
        return 1;  // Condição 1 com probabilidade 0.3
    } else if (probabilidade < 0.5) {
        return 2;  // Condição 2 com probabilidade 0.2
    } else if (probabilidade < 0.7) {
        return 3;  // Condição 3 com probabilidade 0.2
    } else if (probabilidade < 0.85) {
        return 4;  // Condição 4 com probabilidade 0.15
    } else {
        return 5;  // Condição 5 com probabilidade 0.15
    }
}

void gerarLaudo(Fila *filaExames, Fila *filaLaudo,
                int *radiologistasDisponiveis, int tempo) {
    static int numeroPaciente = 1;

    if (!filaVazia(filaExames) && *radiologistasDisponiveis > 0) {
        int idPaciente = desenfileirar(filaExames);
        int tempoPreparoLaudo = rand() % 21 + 10;

        RegistroLaudo novoLaudo;
        novoLaudo.id_paciente = idPaciente;
        int condicao = gerarCondicaoAleatoria();
        novoLaudo.condicao = condicao; // Garante que a condição seja de 1 a 5
        novoLaudo.instante_tempo = tempo + tempoPreparoLaudo;
        novoLaudo.tempo_espera = tempo - novoLaudo.instante_tempo;

        printf("Tempo %d: Laudo para Paciente %d concluído em %d unidades de "
               "tempo. Condição: %d.\n",
               tempo + tempoPreparoLaudo, idPaciente, tempoPreparoLaudo,
               novoLaudo.condicao);

        No *atual = filaLaudo->inicio;
        while (atual != NULL) {
            atual->tempo_espera = tempo - atual->instante_tempo;
            atual = atual->proximo;
        }

        enfileirarLaudo(filaLaudo, numeroPaciente, novoLaudo.condicao,
                        novoLaudo.instante_tempo, novoLaudo.tempo_espera);
        (*radiologistasDisponiveis)++;
        numeroPaciente++;
    }
}




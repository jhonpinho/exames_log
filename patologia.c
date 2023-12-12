// patologia.c
#include "patologia.h"
#define NUMERO_PATOLOGIA 5
Patologia estatisticas_patologias[NUMERO_PATOLOGIA];
Patologia inicializarPatologia(int condicao) {
  Patologia patologia;

  // Ajustar o ID da patologia conforme necessário
  patologia.id_patologia = condicao;
   
  // Inicializar os outros campos
  patologia.total_exames = 0;
  patologia.tempo_total_espera = 0;

  return patologia;
}

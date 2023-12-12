// patologia.h
#ifndef PATOLOGIA_H
#define PATOLOGIA_H
#define NUMERO_PATOLOGIA 5
typedef struct {
    int id_patologia;
    int total_exames;
    int tempo_total_espera;
} Patologia;
Patologia inicializarPatologia(int condicao);
extern Patologia estatisticas_patologias[NUMERO_PATOLOGIA];
#endif

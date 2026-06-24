#pragma once

/*
 * Representa uma instância de tabela de estatísticas.
 */
typedef struct {
    int armazenados;
    int consultas_real;
    int consultas_evit;

    int falsos;
    float falsos_tx;

    float tempo_medio;
    float tempo_acc;
} Estatisticas;

void congelar();

void limpar();

float calcular_tempo();

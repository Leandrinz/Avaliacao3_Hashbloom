#pragma once
#include "hash.h"
#include <stdbool.h>

/*
 * A quantidade de funções de hash que o engenheiro Victor fez.
 */
#define QUANT_HASHERS 2

/*
 * Representa uma instância de um filtro de bloom.
 */
typedef struct {
    int tamanho;
    int (*hashers[QUANT_HASHERS])(int);
    unsigned char *bytes;
} Bloom;

Bloom *iniciar_filtro(int tamanho);

void liberar_filtro(Bloom *filtro);

void inserir_filtro(Bloom *filtro, Usuario *usuario);

bool consultar_filtro(Bloom *filtro, Usuario *usuario);

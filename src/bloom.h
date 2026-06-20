#pragma once
#include "hash.h"

/*
 * Representa uma instância de um filtro de bloom.
 */
typedef struct {
    int tamanho;
    unsigned char *bytes;
} Bloom;

Bloom *iniciar_filtro(int tamanho);

void liberar_filtro(Bloom *filtro);

void inserir_filtro(Bloom *filtro, Usuario *usuario);

bool consultar_filtro(Bloom *filtro, Usuario *usuario);

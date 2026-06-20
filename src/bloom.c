#include "bloom.h"
#include "hash.h"
#include <stdlib.h>

/*
 * Cria um novo filtro na memória.
 */
Bloom *iniciar_filtro(int tamanho) {
    Bloom *saida = malloc(sizeof(Bloom));

    *saida = (Bloom){
        .tamanho = tamanho,
        .bytes = calloc((tamanho / 8) + 1, sizeof(unsigned char)),
    };

    return saida;
}

/*
 * Remove um filtro da memória.
 */
void liberar_filtro(Bloom *filtro) {
    free(filtro->bytes);
    free(filtro);
}

/*
 * Insere um novo nome dentro do filtro.
 */
void inserir_filtro(Bloom *filtro, Usuario *usuario) {
    unsigned int bit_global = HashDivi(usuario->nome_int);

    int byte = bit_global / 8;
    int deslocamento = bit_global % 8;

    filtro->bytes[byte] |= 1 << deslocamento;
}

/*
 * Verifica se um nome está dentro do filtro.
 */
bool consultar_filtro(Bloom *filtro, Usuario *usuario) {
    unsigned int bit_global = HashDivi(usuario->nome_int);

    int byte = bit_global / 8;
    int deslocamento = bit_global % 8;

    return (filtro->bytes[byte] & 1 << deslocamento) != 0;
}

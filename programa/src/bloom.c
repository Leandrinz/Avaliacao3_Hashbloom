#include "bloom.h"
#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>

/*
 * Cria um novo filtro de 'tamanho' bits na memória.
 */
Bloom *iniciar_filtro(int tamanho) {
    Bloom *saida = malloc(sizeof(Bloom));

    *saida = (Bloom){
        .tamanho = tamanho,
        .hashers = {HashDivi, HashPrimoOp},
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
 * Insere um novo usuário dentro do filtro.
 */
void inserir_filtro(Bloom *filtro, Usuario *usuario) {
    for (int i = 0; i < QUANT_HASHERS; i++) {
        int bit_global = filtro->hashers[i](usuario->nome_int);

        int byte = bit_global / 8;
        int deslocamento = bit_global % 8;

        filtro->bytes[byte] |= 1 << deslocamento;
    }
}

/*
 * Verifica se um usuário está dentro do filtro.
 *
 * Se 'true', pode ser que esteja.
 * Se 'false', certamente não está.
 */
bool consultar_filtro(Bloom *filtro, Usuario *usuario) {
    for (int i = 0; i < QUANT_HASHERS; i++) {
        int bit_global = filtro->hashers[i](usuario->nome_int);

        int byte = bit_global / 8;
        int deslocamento = bit_global % 8;

        if ((filtro->bytes[byte] & 1 << deslocamento) == 0) {
            return false;
        };
    }

    return true;
}

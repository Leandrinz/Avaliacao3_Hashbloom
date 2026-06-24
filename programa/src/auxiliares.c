#include "auxiliares.h"
#include <stdio.h>
#include <time.h>

/*
 * Congela e limpa automaticamente o terminal.
 */
void congelar() {
    puts("");
    printf("[Pressione Enter...]");

    getchar();
    while (getchar() != '\n')
        ;

    limpar();
}

/*
 * Limpa o terminal usando ANSI.
 */
void limpar() {
    printf("\033[2J\033[H\033[3J");
}

/*
 * Retorna um timestamp em microsegundos.
 */
float calcular_tempo() {
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);

    return (float)spec.tv_nsec / 1000;
}

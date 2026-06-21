#include "auxiliares.h"
#include <stdio.h>

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

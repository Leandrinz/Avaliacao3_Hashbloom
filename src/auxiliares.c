#include "auxiliares.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Congela e limpa automaticamente o terminal.
 */
void congelar() {
    puts("");
    puts("[Pressione Enter...]");

    while (getchar() != '\n')
        ;

    getchar();
    system("clear");
}

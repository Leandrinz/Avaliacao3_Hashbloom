#include <stdio.h>
#include <stdlib.h>

void congelar() {
    puts("");
    puts("[Pressione Enter...]");

    while (getchar() != '\n')
        ;

    getchar();
    system("clear");
}

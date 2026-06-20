#include "auxiliares.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

TabelaHash tabela;

int main() {
    InicializarTabela(&tabela);
    system("clear");
    puts("Bem-vindo ao Hashbloom!");

    for (;;) {
        int escolha = 0;

        puts("Selecione uma das opções abaixo:");
        puts("    [1] - Modo Inserção");
        puts("    [2] - Modo Consulta");
        puts("    [3] - Modo Estatísticas");
        puts("    [4] - Modo Lote");
        puts("    [?] - Sair");
        puts("");

        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            // Inserção
            congelar();
            break;

        case 2:
            // Consulta
            congelar();
            break;

        case 3:
            // Estatísticas
            congelar();
            break;

        case 4:
            // Lote
            congelar();
            break;

        default:
            // Desconhecido
            exit(0);
        }
    }
}

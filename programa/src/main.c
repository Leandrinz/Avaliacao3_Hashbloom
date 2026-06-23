#include "auxiliares.h"
#include "bloom.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    TabelaHash tabela;
    inicializarTabela(&tabela);

    Bloom *filtro = iniciar_filtro(QUANT_ITENS * 10);

    limpar();
    puts("Bem-vindo ao Hashbloom!");

    for (;;) {
        int escolha = 0;
        char nome_desejado[30] = "";

        puts("Selecione uma das opções abaixo:");
        puts("    [1] - Modo Inserção");
        puts("    [2] - Modo Consulta");
        puts("    [3] - Modo Estatísticas");
        puts("    [4] - Modo Lote");
        puts("    [?] - Sair");
        puts("");

        printf("Escolha: ");
        scanf("%d", &escolha);
        puts("");

        switch (escolha) {
        case 1:
            printf("INSERIR: ");
            scanf("%29s", nome_desejado);

            // Inicia usuário
            Usuario* user= iniciarUsuario(nome_desejado);

            if (consultar_filtro(filtro, user) == false){ // Caso não esteja, inserimos
                Inserir(&tabela, *user);
                inserir_filtro(filtro, user);
            }
            else { // Caso true, buscamos para ver se está mesmo
                Usuario resultado = Busca(&tabela, *user);
                if (resultado.ocupado != -1){
                    printf("Usuário já cadastrado \n");
                }
                else{
                    Inserir(&tabela, *user);
                    inserir_filtro(filtro, user);
                }
            }

            congelar();
            break;

        case 2:
            printf("CONSULTAR: ");
            scanf("%29s", nome_desejado);

            user = iniciarUsuario(nome_desejado);

            Usuario resultado = Busca(&tabela, *user);
            if (resultado.ocupado != -1){
                printf("Usuário já cadastrado \n");
            }
            else{
                puts("Usuário não encontrado");
            }

            congelar();
            break;

        case 3:
            puts("ESTATÍSTICAS:");

            /*
             * Lógica aqui
             */

            printf("    Elementos armazenados: %d\n", -1);
            printf("    Consultas realizadas: %d\n", -1);
            printf("    Consultas evitadas: %d\n", -1);
            printf("    Falsos positivos: %d\n", -1);
            printf("    Taxa de falsos positivos: %.2f\n", -1.);
            printf("    Tempo médio de consulta: %d\n", -1);

            congelar();
            break;

        case 4:
            puts("LOTE:");

            /*
             * Lógica aqui
             */

            congelar();
            break;

        default:
            liberar_filtro(filtro);
            free(tabela.tabela);

            puts("Tchau!");
            exit(0);
        }
    }
}

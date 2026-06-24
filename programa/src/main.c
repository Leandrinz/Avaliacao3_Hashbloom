#include "auxiliares.h"
#include "bloom.h"
#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    TabelaHash tabela;
    inicializarTabela(&tabela);

    Bloom *filtro = iniciar_filtro(QUANT_ITENS * 10);
    Estatisticas estats = {};

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

                estats.consultas_evit++;
                estats.armazenados++;
            }
            else { // Caso true, buscamos para ver se está mesmo
                float tempo_inicial = calcular_tempo();
                Usuario resultado = Busca(&tabela, *user);
                estats.tempo_acc += calcular_tempo() - tempo_inicial;

                if (resultado.ocupado != -1){
                    printf("Usuário já cadastrado \n");
                }
                else{
                    Inserir(&tabela, *user);
                    inserir_filtro(filtro, user);

                    estats.falsos++;
                    estats.armazenados++;
                }

                estats.consultas_real++;
            }
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
            estats.consultas_real++;
            break;

        case 3: {
            puts("ESTATÍSTICAS:");

            if (estats.consultas_real != 0) {
                estats.falsos_tx = (float)estats.falsos / estats.consultas_real;
                estats.tempo_medio = estats.tempo_acc / estats.consultas_real;
            }

            printf("    Elementos armazenados: %d\n", estats.armazenados);
            printf("    Consultas realizadas: %d\n", estats.consultas_real);
            printf("    Consultas evitadas: %d\n", estats.consultas_evit);
            printf("    Falsos positivos: %d\n", estats.falsos);
            printf("    Taxa de falsos positivos: %.2f%%\n", estats.falsos_tx);
            printf("    Tempo médio de consulta: %.1fms\n", estats.tempo_medio);
            break;
        }

        case 4: {
            printf("LOTE: ./dados/arquivos/");

            // Coleta o nome do arquivo.
            char arquivo[40] = "";
            scanf("%39s", arquivo);

            // Concatena com o caminho completo;
            char diretorio[60] = "./dados/arquivos/";
            strcat(diretorio, arquivo);

            // Tenta abrir um arquivo de lote.
            FILE *lote = fopen(diretorio, "r");
            if (lote == NULL) {
                printf("Não foi possível abrir o arquivo '%s'.\n", arquivo);
                break;
            }

            // Lê cada nome de um arquivo de lote e cadastra os usuários.
            while (fscanf(lote, "%29s", nome_desejado) != EOF) {
                Usuario *usuario_tmp = iniciarUsuario(nome_desejado);

                Inserir(&tabela, *usuario_tmp);
                inserir_filtro(filtro, usuario_tmp);
                estats.armazenados++;
            }

            puts("O arquivo foi lido com sucesso!");
            break;
        }

        default:
            liberar_filtro(filtro);
            free(tabela.tabela);

            puts("Tchau!");
            exit(0);
        }

        congelar();
    }
}

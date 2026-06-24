#include "auxiliares.h"
#include "bloom.h"
#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int flag1 = 0, flag2 = 0;
    int tamanho_teste = 10000;

    TabelaHash tabela;
    int *testes_id; // Armazena apenas o nome_int de cada usuário para o teste

    testes_id = malloc(tamanho_teste * sizeof(int));
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

        printf("ESCOLHA: ");
        scanf("%d", &escolha);
        puts("");

        switch (escolha) {
        case 1: {
            printf("INSERIR: ");
            scanf("%29s", nome_desejado);

            bool usuario_existe = false;
            Usuario *usuario_desejado = iniciarUsuario(nome_desejado);

            // Verifica se o usuário está no filtro de bloom.
            if (consultar_filtro(filtro, usuario_desejado)) {
                float tempo_inicial = calcular_tempo();

                // Verifica se o usuário desejado existe na tabela hash.
                if (Busca(&tabela, *usuario_desejado).ocupado != -1) {
                    usuario_existe = true;
                }

                estats.consultas_real++;
                estats.tempo_acc += calcular_tempo() - tempo_inicial;
            } else {
                estats.consultas_evit++;
            }

            if (usuario_existe) {
                puts("Esse usuário já existe.");
            } else {
                Inserir(&tabela, *usuario_desejado);
                inserir_filtro(filtro, usuario_desejado);
                estats.armazenados++;

                puts("Usuário cadastrado com sucesso!");
            }
            break;
        }

        case 2: {
            puts("Selecione uma das opções abaixo:");
            puts("    [1] - Modo com Bloom");
            puts("    [2] - Modo sem Bloom");
            puts("");

            int modo = 0;
            printf("ESCOLHA: ");
            scanf("%d", &modo);

            // Só vendo se o modo é inválido.
            if (modo != 1 && modo != 2) {
                puts("Escolha inválida.");
                break;
            }

            printf("CONSULTAR: ");
            scanf("%29s", nome_desejado);

            bool usuario_existe = false;
            bool pular_filtro = modo == 2;
            Usuario *usuario_desejado = iniciarUsuario(nome_desejado);

            // Verifica se o usuário está no filtro de bloom.
            // Se estiver no modo 'sem filtrar', esse check é sempre verdadeiro.
            if (pular_filtro || consultar_filtro(filtro, usuario_desejado)) {
                float tempo_inicial = calcular_tempo();

                // Verifica se o usuário desejado existe na tabela hash.
                if (Busca(&tabela, *usuario_desejado).ocupado != -1) {
                    usuario_existe = true;
                }

                estats.consultas_real++;
                estats.tempo_acc += calcular_tempo() - tempo_inicial;
            } else if (!pular_filtro) {
                estats.consultas_evit++;
            }

            if (usuario_existe) {
                puts("Usuário encontrado.");
            } else {
                puts("Usuário inexistente.");
            }
            break;
        }

        case 3: {
            if (flag1 == 1 && flag2 == 1) {
                int modo = 1;
                puts("Selecione uma das opções abaixo:");
                puts("    [1] - Dados com bloom");
                puts("    [2] - Dados sem bloom");
                scanf("%d", &modo);

                estats.consultas_real = 0;
                estats.falsos = 0;
                estats.consultas_evit = 0;
                estats.tempo_acc = 0;

                for (int i = 0; i < tamanho_teste; i++) {
                    // Criamos uma struct temporária limpa em pilha apenas com o ID simulado
                    Usuario temp = { .nome_int = testes_id[i], .ocupado = 0 };
                    
                    switch (modo) {
                    case 1:
                        if (consultar_filtro(filtro, &temp) == false) {
                            estats.consultas_evit++;
                        } else {
                            float tempo_inicial = calcular_tempo();
                            Usuario resultado = Busca(&tabela, temp);
                            estats.tempo_acc += calcular_tempo() - tempo_inicial;

                            if (resultado.ocupado == -1) {
                                estats.falsos++;
                            }
                            estats.consultas_real++;
                        }
                        break;
                    case 2:
                        {
                            float tempo_inicial = calcular_tempo();
                            Usuario resultado = Busca(&tabela, temp);
                            estats.tempo_acc += calcular_tempo() - tempo_inicial;
                            
                            if (resultado.ocupado != -1) {
                                // Encontrado
                            }
                            estats.consultas_real++;
                        }
                        break;
                    default:
                        break;
                    }
                }
            } else if (flag1 == 1 && flag2 == 0) {
                puts("Falta inserir o arquivo de teste para dados concretos");
            } else if (flag2 == 1 && flag1 == 0) {
                puts("Falta inserir o arquivo da tabela para dados concretos");
            }

            puts("ESTATÍSTICAS:");

            if (estats.consultas_real != 0) {
                estats.falsos_tx =
                    ((float)estats.falsos / estats.consultas_real) * 100.0f;
                estats.tempo_medio = estats.tempo_acc / estats.consultas_real;
            } else {
                estats.falsos_tx = 0.0f;
                estats.tempo_medio = 0.0f;
            }

            printf("    Elementos armazenados: %d\n", estats.armazenados);
            printf(
                "    Consultas realizadas na tabela: %d\n",
                estats.consultas_real
            );
            printf(
                "    Consultas evitadas pelo bloom: %d\n", estats.consultas_evit
            );
            printf("    Falsos positivos: %d\n", estats.falsos);
            printf("    Taxa de falsos positivos: %.2f%%\n", estats.falsos_tx);
            printf("    Tempo médio de consulta: %.4fms\n", estats.tempo_medio);
            break;
        }

        case 4: {
            puts("Selecione uma das opções abaixo:");
            puts("    [1] - Lote oficial");
            puts("    [2] - Lote teste");
            puts("");
            
            int modo = 0;
            printf("ESCOLHA: ");
            scanf("%d", &modo);
            
            // Só vendo se o modo é inválido.
            if (modo != 1 && modo != 2) {
                puts("Escolha inválida.");
                break;
            }
            
            switch (modo) {
            case 1: {
                printf("LOTE: ./dados/arquivos/");

                char arquivo[40] = "";
                scanf("%39s", arquivo);

                char diretorio[60] = "./dados/arquivos/";
                strcat(diretorio, arquivo);

                FILE *lote = fopen(diretorio, "r");
                if (lote == NULL) {
                    printf("Não foi possível abrir o arquivo '%s'.\n", arquivo);
                    break;
                }

                while (fscanf(lote, "%29s", nome_desejado) != EOF) {
                    Usuario *usuario_tmp = iniciarUsuario(nome_desejado);

                    Inserir(&tabela, *usuario_tmp);
                    inserir_filtro(filtro, usuario_tmp);
                    estats.armazenados++;
                    free(usuario_tmp);
                }

                puts("O arquivo foi lido com sucesso!");
                fclose(lote);
                flag1 = 1;
                break;
            }
            case 2: {
                printf("Teste: ./dados/arquivos/");

                char arquivo[40] = "";
                scanf("%39s", arquivo);

                char diretorio[60] = "./dados/arquivos/";
                strcat(diretorio, arquivo);

                FILE *lote = fopen(diretorio, "r");
                if (lote == NULL) {
                    printf("Não foi possível abrir o arquivo '%s'.\n", arquivo);
                    break;
                }

                int i = 0;
                while (fscanf(lote, "%29s", nome_desejado) != EOF &&
                       i < 10000) {
                    Usuario *usuario_tmp = iniciarUsuario(nome_desejado);
                    testes_id[i] =
                        usuario_tmp
                            ->nome_int; // Armazena estritamente o valor inteiro
                    i++;
                    free(usuario_tmp);
                }

                tamanho_teste = i;

                puts("O arquivo foi lido com sucesso!");
                fclose(lote);
                flag2 = 1;
                break;
            }
            default:
                break;
            }
            break;
        }

        default:
            liberar_filtro(filtro);
            free(tabela.tabela);
            free(testes_id);

            puts("Tchau!");
            exit(0);
        }

        congelar();
    }
}

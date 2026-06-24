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

        printf("Escolha: ");
        scanf("%d", &escolha);
        puts("");

        switch (escolha) {
        case 1:
            printf("INSERIR: ");
            scanf("%29s", nome_desejado);

            Usuario *user = iniciarUsuario(nome_desejado);

            if (consultar_filtro(filtro, user) == false) {
                Inserir(&tabela, *user);
                inserir_filtro(filtro, user);

                estats.consultas_evit++;
                estats.armazenados++;
            } else {
                float tempo_inicial = calcular_tempo();
                Usuario resultado = Busca(&tabela, *user);
                estats.tempo_acc += calcular_tempo() - tempo_inicial;

                if (resultado.ocupado != -1) {
                    printf("Usuário já cadastrado \n");
                } else {
                    Inserir(&tabela, *user);
                    inserir_filtro(filtro, user);

                    estats.falsos++;
                    estats.armazenados++;
                }
                estats.consultas_real++;
            }
            free(user);
            break;

        case 2: {
            int modo = 1;
            puts("Selecione uma das opções abaixo:");
            puts("    [1] - Modo Com Bloom");
            puts("    [2] - Modo Sem Bloom");
            scanf("%d", &modo);
            printf("CONSULTAR: ");
            scanf("%29s", nome_desejado);

            Usuario *temp = iniciarUsuario(nome_desejado);

            switch (modo) {
            case 1:
                if (consultar_filtro(filtro, temp) == false) {
                    puts("A pessoa buscada esta fora da tabela");
                    estats.consultas_evit++;
                } else {
                    float tempo_inicial = calcular_tempo();
                    Usuario resultado = Busca(&tabela, *temp);
                    estats.tempo_acc += calcular_tempo() - tempo_inicial;

                    if (resultado.ocupado != -1) {
                        printf("Usuário encontrado \n");
                    } else {
                        puts("A pessoa buscada esta fora da tabela");
                        estats.falsos++;
                    }
                    estats.consultas_real++;
                }
                free(temp);
                break;
            case 2:
                {
                    Usuario resultado = Busca(&tabela, *temp);
                    if (resultado.ocupado != -1) {
                        printf("Usuário já cadastrado \n");
                    } else {
                        puts("Usuário não encontrado");
                    }
                    estats.consultas_real++;
                    free(temp);
                }
                break;
            default:
                free(temp);
                break;
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
                estats.falsos_tx = ((float)estats.falsos / estats.consultas_real) * 100.0f;
                estats.tempo_medio = estats.tempo_acc / estats.consultas_real;
            } else {
                estats.falsos_tx = 0.0f;
                estats.tempo_medio = 0.0f;
            }

            printf("    Elementos armazenados: %d\n", estats.armazenados);
            printf("    Consultas realizadas na tabela: %d\n", estats.consultas_real);
            printf("    Consultas evitadas pelo Bloom: %d\n", estats.consultas_evit);
            printf("    Falsos positivos: %d\n", estats.falsos);
            printf("    Taxa de falsos positivos: %.2f%%\n", estats.falsos_tx);
            printf("    Tempo médio de consulta: %.4fms\n", estats.tempo_medio);
            break;
        }

        case 4: {
            int modo = 1;
            puts("Selecione uma das opções abaixo:");
            puts("    [1] - Modo Lote oficial");
            puts("    [2] - Modo Lote teste");
            scanf("%d", &modo);

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
                while (fscanf(lote, "%29s", nome_desejado) != EOF && i < 10000) {
                    Usuario *usuario_tmp = iniciarUsuario(nome_desejado);
                    testes_id[i] = usuario_tmp->nome_int; // Armazena estritamente o valor inteiro
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
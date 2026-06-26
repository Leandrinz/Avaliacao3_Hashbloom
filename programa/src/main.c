#include "auxiliares.h"
#include "bloom.h"
#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Hash
    TabelaHash tabela;
    inicializarTabela(&tabela);

    // Bloom
    Bloom *filtro = iniciar_filtro(QUANT_ITENS * 10);
    Estatisticas estats = {};

    //Teste
    bool carregado_tabela = false;
    bool exibir_dados_teste = false;
    Estatisticas dados_teste_bloom = {};
    Estatisticas dados_teste_hash = {};

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
                else {
                    estats.falsos++;
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

            free(usuario_desejado);
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
                else {
                    estats.falsos++;
                }

                estats.consultas_real++;
                estats.tempo_acc += calcular_tempo() - tempo_inicial;
            } else {
                estats.consultas_evit++;
            }

            if (usuario_existe) {
                puts("Usuário encontrado.");
            } else {
                puts("Usuário inexistente.");
            }

            free(usuario_desejado);
            break;
        }

        case 3: {
            puts("ESTATÍSTICAS:");

            

            if(!exibir_dados_teste) {
                if (estats.consultas_real != 0) {
                    estats.falsos_tx = (float)estats.falsos / estats.consultas_real;
                    estats.tempo_medio = estats.tempo_acc / estats.consultas_real;
                    }

                printf("    Elementos armazenados: %d\n", estats.armazenados);
                printf("    Consultas realizadas na tabela: %d\n", estats.consultas_real);
                printf("    Consultas evitadas pelo bloom: %d\n", estats.consultas_evit);
                printf("    Falsos positivos: %d\n", estats.falsos);
                printf("    Taxa de falsos positivos: %.2f%%\n", estats.falsos_tx * 100);
                printf("    Tempo médio de consulta: %.1fms\n", estats.tempo_medio);
            }
            else {
                puts("DADOS COM BLOOM:");
                 if (dados_teste_bloom.consultas_real != 0) {
                    dados_teste_bloom.falsos_tx = (float)dados_teste_bloom.falsos / dados_teste_bloom.consultas_real;
                    dados_teste_bloom.tempo_medio = dados_teste_bloom.tempo_acc / dados_teste_bloom.consultas_real;
                    }

                printf("    Consultas realizadas na tabela: %d\n", dados_teste_bloom.consultas_real);
                printf("    Consultas evitadas pelo bloom: %d\n", dados_teste_bloom.consultas_evit);
                printf("    Falsos positivos: %d\n", dados_teste_bloom.falsos);
                printf("    Taxa de falsos positivos: %.2f%%\n", dados_teste_bloom.falsos_tx * 100);
                printf("    Tempo médio de consulta: %.1fms\n", dados_teste_bloom.tempo_medio);

                puts("DADOS SEM BLOOM:");
                if (dados_teste_hash.consultas_real != 0) {
                    dados_teste_hash.tempo_medio = dados_teste_hash.tempo_acc / dados_teste_hash.consultas_real;
                    }

                printf("    Consultas realizadas na tabela: %d\n", dados_teste_hash.consultas_real);
                printf("    Tempo médio de consulta: %.1fms\n", dados_teste_hash.tempo_medio);

                puts("    [1] - Parar de exibir testes e resetar suas estatisticas");
                puts("    [2] - Sair dessa aba (qualquer tecla)");
                puts("");

                int modo = 0;
                printf("ESCOLHA: ");
                scanf("%d", &modo);
                if(modo == 1) {
                    exibir_dados_teste = false;
                    dados_teste_bloom = (Estatisticas){0};
                    dados_teste_hash = (Estatisticas){0};
                }
            }
            break;
        }

        case 4: {
            //Informa quais arquivos ja foram carregados e estao no sistema
            

            puts("Selecione uma das opções abaixo:");
            puts("    [1] - Lote oficial");
            puts("    [2] - Realizar testes em lote");
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
                carregado_tabela = true;
                break;
            }
            case 2: {
                //Criar estatistica proprias para teste de lote
                if(!carregado_tabela) {
                    puts("Falta os valores originais para realizar um teste");
                    puts("Porfavor os insira na opçao 1 dessa pagina");
                    break;
                }
                if(exibir_dados_teste) {
                    puts("Seu teste esta pronto, pfvr visualize na aba estatistica");
                    break;
                }

                int tamanho_teste = 0;
                Usuario *valores_teste;

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

                while (fscanf(lote, "%29s", nome_desejado) != EOF) {
                    tamanho_teste++;
                }
                valores_teste = malloc(tamanho_teste*sizeof(Usuario));
                //Retorna o ponteiro de leitura para o começo
                rewind(lote);

                int pivo_temp = 0;
                while (fscanf(lote, "%29s", nome_desejado) != EOF) {
                    Usuario *temp = iniciarUsuario(nome_desejado);
                    nomeToInt(temp);

                    strcpy(valores_teste[pivo_temp].nome, temp->nome);
                    valores_teste[pivo_temp].nome_int = temp->nome_int;
                    valores_teste[pivo_temp].ocupado = temp->ocupado;
                    pivo_temp++;
                    free(temp);
                }

                puts("O arquivo foi lido com sucesso!");
                fclose(lote);
                          
                    for(int i = 0; i < tamanho_teste; i++) {
                        // Criamos uma struct temporária 
                        Usuario temp = valores_teste[i];

                        if (consultar_filtro(filtro, &temp) == false) {
                            dados_teste_bloom.consultas_evit++;
                        } else {
                            float tempo_inicial1 = calcular_tempo();
                            Usuario resultado = Busca(&tabela, temp);
                            dados_teste_bloom.tempo_acc += calcular_tempo() - tempo_inicial1;

                            if (resultado.ocupado == -1) {
                                dados_teste_bloom.falsos++;
                            }
                            dados_teste_bloom.consultas_real++;
                        }

                        float tempo_inicial2 = calcular_tempo();
                            Usuario resultado = Busca(&tabela, temp);
                            dados_teste_hash.tempo_acc += calcular_tempo() - tempo_inicial2;

                            if (resultado.ocupado != -1) {
                                // Encontrado
                            }
                            dados_teste_hash.consultas_real++;
                    }
                 
                exibir_dados_teste = true;
                free(valores_teste);
                puts("Os resultados se encontram na aba estatistica");
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

            puts("Tchau!");
            exit(0);
        }

        congelar();
    }
}

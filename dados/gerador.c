#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
    Codigo utilizado para gerar os arquivos de teste, compile de maneira independente
*/
void gerar(int n, char lista[][12]) {
    /*
        Função para inserir de maneira aleatória elementos dentro da lista
        de tamanho n. Todos os textos tem tamanho fixo de 8 char 3 int
    */
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 11; j++) {
            if(j < 8) {
                //Uso da biblioteca rand junto com tabela ASCII para converter um valor inteiro para char
                lista[i][j] = (rand() % 26)+97;
            }
            else {
                lista[i][j] = (rand() %10)+48;
            }
            //Adição do caractere final
            lista[i][11] = '\0';
        }
    }
}

int main(int argc, char *argv[]) {
    // Tratamento de ausência de argumentos.
    if (argc <= 1) {
        fprintf(
            stderr, "Insira o tamanho desejado como argumento do programa.\n"
        );
        exit(1);
    }

    // Tratamento de argumento inválido.
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Insira um número inteiro positivo.\n");
        exit(1);
    }
    char lista[n][12];

    //Definindo uma semente aleatória para o rand
    srand(time(NULL));
    gerar(n, lista);
    //Gravando o arquivo. OBS: Ao alterar o n se altera o nome do arquivo
    char nome [50];
    sprintf(nome, "./dados/arquivos/lista%d.txt", n);
    FILE *file = fopen(nome, "w");
    for(int i = 0; i < n; i++){
        fprintf(file, "%s\n", lista[i]);
    }
    fclose(file);
    printf("Lista gerada com sucesso!\n");
    return 0;
}

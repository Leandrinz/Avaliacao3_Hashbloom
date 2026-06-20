#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
    Codigo utilizado para gerar os arquivos de teste, compile de maneira idependente
    OBS: Para gerar arquivos de tamanho diferente apenas altere o n
*/
#define n 100000
char lista[n][12];

int gerar() {
    /*
        Funçao para inserir de maneira aleatoria elementos dentro da lista
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
            //Adiçao do caractere final
            lista[i][11] = '\0';
        }
    }
}

int main() {
    //Definindo uma semente aleatoria para o rand
    srand(time(NULL));
    gerar();
    //Gravando o arquivo. OBS: Ao alterar o n se altera o nome do arquivo
    char nome [50];
    sprintf(nome, "./arquivos/lista%d.txt", n);
    FILE *file = fopen(nome, "w");
    for(int i = 0; i < n; i++){
        fprintf(file, "%s\n", lista[i]);
    }
    fclose(file);
    printf("Lista gerada com sucesso!\n");
    return 0;
}
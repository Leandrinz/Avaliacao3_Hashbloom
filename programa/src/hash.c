#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Usuario *iniciarUsuario(char *nome) {
    Usuario *saida = malloc(sizeof(Usuario));

    strcpy(saida->nome, nome);
    nomeToInt(saida);
    saida->ocupado = 0;

    return saida;
}

/*
    Conversao de texto para um valor inteiro
*/
void nomeToInt(Usuario *user) {
    int valor = 0;
    for(int i = 0; i < (int)strlen(user->nome); i++) {
        valor += user->nome[i];
    }
    user->nome_int = valor;
    return;
}

//Necessaria para garantir a segurança
void inicializarTabela(TabelaHash *tab) {
    tab->tabela = malloc(QUANT_ITENS*sizeof(Usuario));
    for(int i = 0; i < QUANT_ITENS; i++) {
        tab->tabela[i].nome[0] = '\0';
        tab->tabela[i].nome_int = 0;
        tab->tabela[i].ocupado = 0;
    }
    return;
}

int HashDivi(int user) {
    return user % QUANT_ITENS;
}
int HashPrimoOp(int user) {
    int temp = (5*user + 13) % QUANT_ITENS;
    if(temp != 0) {
        return temp;
    }
    return 1;
}
//DoubleHash utilizado para o tratamento de colisoes por endereçamento aberto
int DoubleHash(int user, int i) {
    return (HashDivi(user)+HashPrimoOp(user)*(i-1)) % QUANT_ITENS;

}

/*
    O metodo de tratamento de colisoes escolhido e o double hash
    sendo um metodo de encdereçamento aberto
*/
//Use essa funçao para inserir na tabela, crie um usuario temporario e insira o nome dele
void Inserir(TabelaHash* tab, Usuario user) {
    int pivo = 2, lock = 1;
    nomeToInt(&user);

    //Funçao hash escolhida e a de divisao simples
    int endereco = HashDivi(user.nome_int);

    //Verifica-se se nao esta ocorrendo colisao
    if(tab->tabela[endereco].ocupado == 0) {
        tab->tabela[endereco] = user;
        tab->tabela[endereco].ocupado = 1;
        return;
    }
    else {
        //Em caso de colisao de entra num sistema de endereçamento aberto para solucionar a colisao
        while(lock) {
            endereco = DoubleHash(user.nome_int, pivo);
            if(tab->tabela[endereco].ocupado == 0) {
                tab->tabela[endereco] = user;
                tab->tabela[endereco].ocupado = 1;
                return;
            }
            pivo++;
            if(pivo > QUANT_ITENS) {
                lock = 0;
            }
        }
    }
}
//Use essa funçao para buscar na tabela, crie um usuario temporario e insira o nome dele
Usuario Busca(TabelaHash *tab, Usuario user) {
    int lock = 1, pivo = 2;
    nomeToInt(&user);
    int endereco = HashDivi(user.nome_int);
    if(tab->tabela[endereco].ocupado == 1 && strcmp(tab->tabela[endereco].nome, user.nome) == 0) {
        return tab->tabela[endereco];
    }
    else {
        while(lock) {
            endereco = DoubleHash(user.nome_int, pivo);

            if(tab->tabela[endereco].ocupado == 0) break;

            if(tab->tabela[endereco].ocupado == 1 && strcmp(tab->tabela[endereco].nome, user.nome) == 0) {
                return tab->tabela[endereco];
            }
            pivo++;
            if(pivo > QUANT_ITENS) {
                lock = 0;
            }
        }
    }

    Usuario error;
    strcpy(error.nome, "ERROR");
    error.nome_int = -1;
    error.ocupado = -1;
    return error;
};

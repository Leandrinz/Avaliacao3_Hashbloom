#pragma once

typedef struct {
    char nome [12];
    int nome_int;
    int ocupado;
} Usuario;

typedef struct {
    Usuario *tabela;
} TabelaHash;

/*
 * A quantidade máxima de usuários na tabela.
 */
#define QUANT_ITENS 1000003

/*
    nomeToInt e uma funçao usada para facilitar operaçoes de hash
*/
void inicializarTabela(TabelaHash*);
void nomeToInt(Usuario *user);
int HashDivi(int);
int HashPrimoOp(int);
int DoubleHash(int,int);
void Inserir(TabelaHash*, Usuario);
Usuario Busca(TabelaHash *tab,Usuario );

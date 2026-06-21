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
    nomeToInt e uma funçao usada para facilitar operaçoes de hash
*/
void inicializarTabela(TabelaHash*);
void nomeToInt(Usuario *user);
int HashDivi(int);
int HashPrimoOp(int);
int DoubleHash(int,int);
void Inserir(TabelaHash*, Usuario);
Usuario Busca(TabelaHash,Usuario);

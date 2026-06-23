#include <unity.h>
#include "hash.h"
#include <string.h>
#include <stdlib.h>


TabelaHash *tab;


void setUp(void)
{
    tab = malloc(sizeof(TabelaHash));

    InicializarTabela(tab);
}


void tearDown(void)
{
    free(tab);
}



/*
    nomeToInt
*/

void test_nomeToInt(void)
{
    Usuario u;

    strcpy(u.nome,"ABC");

    nomeToInt(&u);

    TEST_ASSERT_EQUAL_INT(
        'A'+'B'+'C',
        u.nome_int
    );
}



void test_nomeToInt_vazio(void)
{
    Usuario u;

    u.nome[0]='\0';

    nomeToInt(&u);

    TEST_ASSERT_EQUAL_INT(
        0,
        u.nome_int
    );
}





/*
    Inicializar tabela
*/

void test_inicializarTabela(void)
{

    TEST_ASSERT_EQUAL_INT(
        0,
        tab->tabela[0].ocupado
    );


    TEST_ASSERT_EQUAL_INT(
        0,
        tab->tabela[500].ocupado
    );


    TEST_ASSERT_EQUAL_CHAR(
        '\0',
        tab->tabela[0].nome[0]
    );

}





/*
    Hash
*/

void test_hashDivi(void)
{

    int valor = HashDivi(1000013);


    TEST_ASSERT_EQUAL_INT(
        10,
        valor
    );


    TEST_ASSERT_TRUE(
        valor < 1000003
    );

}




void test_hashPrimoOp(void)
{

    int valor = HashPrimoOp(500);


    TEST_ASSERT_TRUE(
        valor > 0
    );


    TEST_ASSERT_TRUE(
        valor < 1000003
    );

}




void test_doubleHash(void)
{

    for(int i=1;i<100;i++)
    {

        int pos = DoubleHash(500,i);


        TEST_ASSERT_TRUE(
            pos >= 0
        );


        TEST_ASSERT_TRUE(
            pos < 1000003
        );

    }

}




/*
    Inserção simples
*/

void test_inserir(void)
{

    Usuario u;

    strcpy(u.nome,"Ana");


    Inserir(tab,u);


    Usuario r = Busca(tab,u);



    TEST_ASSERT_EQUAL_STRING(
        "Ana",
        r.nome
    );

}





/*
    Busca inexistente
*/

void test_busca_inexistente(void)
{

    Usuario u;


    strcpy(u.nome,"Carlos");


    Usuario r = Busca(tab,u);



    TEST_ASSERT_EQUAL_STRING(
        "ERROR",
        r.nome
    );

}





/*
    Varios usuários
*/

void test_variosUsuarios(void)
{

    Usuario a,b,c;


    strcpy(a.nome,"Ana");
    strcpy(b.nome,"Bruno");
    strcpy(c.nome,"Carlos");


    Inserir(tab,a);
    Inserir(tab,b);
    Inserir(tab,c);



    TEST_ASSERT_EQUAL_STRING(
        "Ana",
        Busca(tab,a).nome
    );


    TEST_ASSERT_EQUAL_STRING(
        "Bruno",
        Busca(tab,b).nome
    );


    TEST_ASSERT_EQUAL_STRING(
        "Carlos",
        Busca(tab,c).nome
    );

}





/*
    Colisão real
*/

void test_colisao(void)
{

    Usuario a,b;


    strcpy(a.nome,"AB");
    strcpy(b.nome,"BA");


    Inserir(tab,a);
    Inserir(tab,b);



    Usuario r1 = Busca(tab,a);
    Usuario r2 = Busca(tab,b);



    TEST_ASSERT_EQUAL_STRING(
        "AB",
        r1.nome
    );


    TEST_ASSERT_EQUAL_STRING(
        "BA",
        r2.nome
    );

}





/*
    Inserção deixa posição ocupada
*/

void test_posicaoOcupada(void)
{

    Usuario u;


    strcpy(u.nome,"Teste");


    Inserir(tab,u);



    nomeToInt(&u);


    int pos = HashDivi(u.nome_int);



    TEST_ASSERT_EQUAL_INT(
        1,
        tab->tabela[pos].ocupado
    );

}





/*
    Busca depois de colisão
*/

void test_buscaDepoisColisao(void)
{

    Usuario a,b;


    strcpy(a.nome,"AB");
    strcpy(b.nome,"BA");



    Inserir(tab,a);
    Inserir(tab,b);



    Usuario r = Busca(tab,b);



    TEST_ASSERT_EQUAL_STRING(
        "BA",
        r.nome
    );

}






#include <unity.h>
#include <string.h>
#include "hash.h"

void setUp(void){}

void tearDown(void){}


// Teste -> nomeToInt(Usuario *user)
void test_nomequalquer(void){
    Usuario u;
    strcpy(u.nome, "Leandro");

    nomeToInt(&u);

    TEST_ASSERT_EQUAL_INT(709, u.nome_int);
}





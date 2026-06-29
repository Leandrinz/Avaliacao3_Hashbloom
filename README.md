# Hashbloom

Repositório destinado ao desenvolvimento do trabalho da terceira avaliação da disciplina de Laboratório de Algoritmos e Estrutura de Dados II.

## Integrantes

- Jozenias Antônio de Oliveira Filho
- Victor Manuel Fernandes Anacleto
- Pedro Henrique Queiroz
- Leandro Savio Barros Gomes

## Instruções de Compilação

Para realizar a compilação, é necessário utilizar o compilador [GCC](https://gcc.gnu.org/) (v14 ou mais recente), ou qualquer outro que ofereça suporte ao padrão C23.

O repositório inclui um Makefile para facilitar a compilação do programa principal e do gerador de lotes de usuários aleatórios utilizando o programa [Make](https://www.gnu.org/software/make/).

É importante lembrar que o Makefile está configurado apenas para ambientes POSIX, caso você esteja em um Windows, irá precisar de uma shell que respeite esse formato para compilar.

### Compilação Normal

Para compilar e executar automaticamente o programa. Basta chamar o Make utilizando a regra padrão.

```bash
make
```

### Geração de Lotes

Para compilar o gerador e gerar um arquivo de lote, é necessário utilizar a regra `gerador` com um parâmeto `ARGS` que representa a quantidade de nomes no arquivo. Abaixo segue um exemplo de geração de 100 nomes aleatórios.

```bash
make gerador ARGS=100
```

Se a execução for bem-sucedida, um arquivo `listaQUANTIDADE.txt` aparecerá na pasta `./dados/arquivos/`.

### Compilação Debug

Para analisar o programa linha por linha, basta executar a regra `debug`.

```bash
make debug
```

### Compilação Manual

Caso você não queira usar o Make, mas ainda tenha acesso a um ambiente POSIX, você pode passar diretamente os parâmetros ao GCC.

```bash
gcc $(find ./programa/src/ -name "*.c") -o ./bin/hashbloom
```

Caso você esteja em um ambiente diferente, será necessário substituir a chamada do comando `find` pelo nome de todos os arquivos `.c` que estão dentro da pasta `./programa/src/`.

## Testes Unitários

### Como Rodar

#### 1º Passo: Instale a linguagem Ruby

Verifique no terminal se você já possui ela instalada com:

```terminal
ruby --version
```

Caso dê erro, significa que você ainda precisa baixar.

Nesse caso, acesse o site oficial da linguagem:

[Site Oficial](https://www.ruby-lang.org/pt/)

Após instalar, execute novamente o comando no terminal para confirmar que tudo está funcionando corretamente.



#### 2º Passo: Instalação do Ceedling


Para instalar, no terminal, digite o comando:

```terminal
gem install ceedling
```

#### 3º Passo: Rodar testes
Entre dentro da pasta raiz dos testes

![alt text](./imagens/image.png)

Rode no terminal:
```
ceedling test:all
```

Resultado esperado:

![alt text](./imagens/image-1.png)



## Exemplos de Execução

O programa foi projetado para ser altamente intuitivo, com poucos menus e mensagens de informativas fáceis de entender. Segue abaixo um exemplo do menu principal.

```text
[1] - Modo Inserção
[2] - Modo Consulta
[3] - Modo Estatísticas
[4] - Modo Lote
[?] - Sair
```

### Inserção Simples

Para realizar uma inserção simples, basta navegar até a opção 1 e digitar o nome de usuário desejado. O programa informará logo em seguida se a inserção foi bem-sucedida ou não.

```text
ESCOLHA: 1

INSERIR: Guilherme
Usuário cadastrado com sucesso!
```

### Consulta

Para realizar uma consulta é bem parecido, basta escolher a opção 2 e digitar o nome desejado. O programa perguntará se a consulta deve ser utilizada com ou sem filtro de bloom.

```text
ESCOLHA: 2

Selecione uma das opções abaixo:
    [1] - Modo com Bloom
    [2] - Modo sem Bloom

ESCOLHA: 1

CONSULTAR: Matheus
Usuário inexistente.
```

### Verificando Estatísticas

Para verificar as estatísticas da execução do programa, pasta escolher a opção 3. No exemplo abaixo, como todas as consultas a tabela hash foram barradas pelo bloom, o tempo médio de consulta está zerado.

```text
ESCOLHA: 3

ESTATÍSTICAS:
    Elementos armazenados: 1
    Consultas realizadas na tabela: 0
    Consultas evitadas pelo bloom: 2
    Falsos positivos: 0
    Taxa de falsos positivos: 0.00%
    Tempo médio de consulta: 0.0ms
```

### Inserção em Lote

Para carregar vários usuários de um arquivo `.txt`, basta utilizar a opção 4 e escolher o modo 1. Logo em seguida, basta colocar o nome do arquivo relativo a pasta `.dados/arquivos/` do projeto.

```
ESCOLHA: 4

Selecione uma das opções abaixo:
    [1] - Carregar Lote
    [2] - Realizar Testes em Lote

ESCOLHA: 1

LOTE: ./dados/arquivos/lista1000.txt
O arquivo foi lido com sucesso!
```

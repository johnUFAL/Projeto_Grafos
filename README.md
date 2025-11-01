# Implementação de algoritmos em Grafos 

## Algoritmos Implementados:

### 1. Algoritmo de Kosaraju 

**Problema que resolve:** Encotrar componentes fortemente conexas em grafos direcionados.

**Como usar:**

```bash
./kosaraju -f <arquivo_de_entrada> [-o <arquivo_de_saida>] [-h]

```

**Parâmetros:**
- `-f <arquivo>` : Especifica o arquivo de entrada com o grafo
- `-o <arquivo>` : Redireciona a saída para um arquivo
- `-h` : Mostra ajuda

**Formato de saída:** Lista as componentes fortemente conexas, uma por linha.

### 2. Algoritmo de Prim

**Problema que resolve:** Encontrar a Árvore Geradora Mínima (AGM) em grafos não direcionados e ponderados.

**Como usar:**

```bash
./prim -f <arquivo_de_entrada> -i <verticie_inicial> [-o <arquivo_de_saida>] [-s] [-h]

```

**Parâmetros:**
- `-f <arquivo>` : Especifica o arquivo de entrada com o grafo
- `-i <vertice>` : Vértice inicial para o algoritmo
- `-s` : Mostra a solução (aresta da AGM)
- `-o <arquivo>` : Redireciona a saída para um arquivo
- `-h` : Mostra ajuda

**Formato de saída:** Custo total da AGM ou lista de arestas de usar `-s`.

### 3. Algoritmo de Kruskal

**Problema que resolve:** Encontrar a Árvore Geradora Mínima (AGM) usando abordagem baseada em união-busca.

**Como usar:**

```bash
./kruskal -f <arquivo_de_entrada> [-o <arquivo_de_saida>] [-s] [-h]

```

**Parâmetros:**
- `-f <arquivo>` : Especifica o arquivo de entrada com o grafo
- `-s` : Mostra a solução (aresta da AGM)
- `-o <arquivo>` : Redireciona a saída para um arquivo
- `-h` : Mostra ajuda

**Formato de saída:** Custo total da AGM ou lista de arestas de usar `-s`.

### 4. Algoritmo de Dijkstra

**Problema que resolve:** Encontrar os caminhos mínimos de um vértice origem para todos os outros vértices em grafos com peso não negativos.

**Como usar:**

```bash
./dijkstra -f <arquivo_de_entrada> -i <verticie_inicial> [-o <arquivo_de_saida>] [-h]

```

**Parâmetros:**
- `-f <arquivo>` : Especifica o arquivo de entrada com o grafo
- `-i <vertice>` : Vértice inicial para o algoritmo
- `-o <arquivo>` : Redireciona a saída para um arquivo
- `-h` : Mostra ajuda

**Formato de saída:** Distância de vértice origem para os outros vértices on formato `vértice:distância`.

## Formato do Arquivo de Entrada 

O arquivo de entrada deve seguir o formato:

```bash
n m 
v1 v2 peso
v1 v2 peso
...

```

Onde:

- `n`: número de vértices
- `m`: nu´mero de arestas
- Cada linha seguinte representa uma aresta: v1 v2 peso

## Estrutura do Projeto

Cada algoritmo esta em sua respectiva pasta contendo:
- Código fonte em C++
- Makefile para compilar 

## Compilação

Em cada pasta, faça:

```bash
make
```
E para limpar os arquivos gerados: 

```bash
make clean
```
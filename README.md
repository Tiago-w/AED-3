# Trabalho Prático: Problema do Caixeiro Viajante (TSP)

Programa desenvolvido em C para resolução do Problema do Caixeiro Viajante utilizando:

* **Algoritmo aproximativo:** heurística do vizinho mais próximo.
* **Algoritmo Exato (força bruta):** busca recursiva com backtracking.

O programa calcula o custo da solução, tempo de execução e gap em relação ao valor ótimo conhecido.

## Estrutura

Os arquivos devem estar organizados da seguinte forma:


```text
meu_trabalho/
├── src/
│   └── main.c
└── docs/
    ├── tsp1_253.txt
    ├── tsp2_1248.txt
    ├── tsp3_1194.txt
    ├── tsp4_7013.txt
    └── tsp5_27603.txt
```

O programa utiliza o caminho relativo ../docs/ para acessar os arquivos.

## Dependências

É necessário apenas um compilador C, como o GCC.

Bibliotecas utilizadas:

stdio.h
stdlib.h
time.h

## Compilação

Na pasta src:


gcc main.c -o tsp


## Execução

Na mesma pasta da compilação:

### Linux


./tsp


### Windows

tsp

## Funcionamento

Ao executar, selecione uma das opções disponíveis no menu.

Para cada instância, o programa executa o algoritmo aproximativo e o algortimo exato, apresentando:

* valor ótimo conhecido;
* custo encontrado;
* tempo de execução;
* gap da solução.

A força bruta é interrompida caso ultrapasse **10 segundos** de execução.

## Gap

O gap é calculado por:

Gap = ((custo encontrado - valor ótimo) / valor ótimo) × 100

Um gap de 0% indica que o custo encontrado é igual ao valor ótimo conhecido.

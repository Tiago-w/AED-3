# Trabalho Prático: Problema do Caixeiro Viajante (TSP) Euclidiano

Este arquivo contém as instruções passo a passo para compilar e executar o código desenvolvido para a solução do Problema do Caixeiro Viajante (TSP). O programa lê matrizes de adjacência fornecidas e calcula a rota utilizando duas abordagens distintas: um algoritmo aproximativo (heurística do vizinho mais próximo) e um algoritmo exato (força bruta).

## Dependências
O código foi desenvolvido inteiramente em C e não possui dependências externas ou bibliotecas adicionais que precisem de instalação. Utiliza apenas as bibliotecas padrão da linguagem (stdio.h, stdlib.h, string.h e time.h). É apenas necessário ter um compilador C (como o GCC) instalado no sistema.



## Instruções de Compilação
No terminal, navegue até a pasta onde se encontra o código-fonte (por exemplo, a pasta src) e execute o comando de compilação:


gcc main.c -o tsp

Este comando vai gerar um arquivo executável chamado tsp.

## Instruções de Execução
Com o código compilado, execute o programa a partir do terminal:

**Em ambiente Linux**

./tsp


**Em ambiente Windows:**

tsp.exe


## Estrutura de Arquivos
Para evitar erros de leitura ("Erro ao abrir o arquivo."), observe para manter a organização das pastas. O código (main.c) utiliza caminhos relativos (../docs/) para procurar os arquivos de texto. A estrutura deve ser semelhante a esta:

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

## Como utilizar o programa
1. Ao iniciar, será apresentado um menu com as opções de arquivos a testar (opções 1 a 5).
2. Digite o número da instância desejada e pressione enter.
3. O programa vai ler a matriz do arquivo correspondente. O custo ótimo já está embutido no código (baseado no nome do arquivo).
4. Para cada execução, o programa irá calcular e registrar na tela o tempo de execução e o custo da solução final.
5. Será também exibido o gap (diferença em porcentagem) da qualidade da solução do algoritmo aproximativo em relação ao custo ótimo fornecido.
"# AED-3" 

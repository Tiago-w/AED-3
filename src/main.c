#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **ler_arquivo(const char *caminho_arquivo, int *numero_vertices_colunas)
{
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int total_elementos = 0;
    int temp;
    while (fscanf(arquivo, "%d", &temp) == 1)
    {
        total_elementos++;
    }

    // descobrir os vertices com os numeros dos elementos internos (arestas)
    int n = 0;
    while (n * n < total_elementos)
    {
        n++;
    }

    // pra devolver
    *numero_vertices_colunas = n;

    // cria matriz
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }

    rewind(arquivo);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    fclose(arquivo);

    return matriz;
}

// heuristica de pegar o vertice mais próximo a partir de um vertice qualquer
int algoritmo_aproximativo(int **matriz, int n)
{
    int visitados[n];

    for (int i = 0; i < n; i++)
    {
        visitados[i] = 0;
    }

    int cidade_atual = 0;
    int custo_total = 0;

    visitados[0] = 1;

    for (int i = 0; i < n - 1; i++)
    {
        int menor = 9999999;
        int proxima = 0;

        for (int j = 0; j < n; j++)
        {
            if (visitados[j] == 0)
            {
                if (matriz[cidade_atual][j] < menor)
                {
                    menor = matriz[cidade_atual][j];
                    proxima = j;
                }
            }
        }

        visitados[proxima] = 1;
        custo_total = custo_total + menor;
        cidade_atual = proxima;
    }

    custo_total = custo_total + matriz[cidade_atual][0];

    return custo_total;
}

int algoritmo_forca_bruta(
    int **matriz,
    int n,
    int cidade_atual,
    int custo_atual,
    int quantidade_visitados,
    int *visitados, clock_t tempo_inicio, int limite_segundos, int *estourou)
{

    clock_t tempo_atual = clock();
    if ((int)(tempo_atual - tempo_inicio) / CLOCKS_PER_SEC > limite_segundos)
    {
        *estourou = 1;
        return 9999999;
    }

    // todas as cidades foram visitadas
    if (quantidade_visitados == n)
    {
        return custo_atual + matriz[cidade_atual][0];
    }

    int menor_custo = 9999999;

    // testa todas as cidades ainda não visitadas
    for (int i = 0; i < n; i++)
    {
        if (visitados[i] == 0)
        {
            visitados[i] = 1;

            int custo = algoritmo_forca_bruta(
                matriz,
                n,
                i,
                custo_atual + matriz[cidade_atual][i],
                quantidade_visitados + 1,
                visitados, tempo_inicio, limite_segundos, estourou);

            if (custo < menor_custo)
            {
                menor_custo = custo;
            }

            // desfaz a escolha para testar outra possibilidade
            visitados[i] = 0;
        }
    }

    return menor_custo;
}

int main()
{
    int numeros_vc, otimo, opcao;
    const char *nome_arquivo;

    do
    {
        printf("Digite o arquivo a ser testado: \n\n");
        printf("1 - tsp1_253.txt\n");
        printf("2 - tsp2_1248.txt\n");
        printf("3 - tsp3_1194.txt\n");
        printf("4 - tsp4_7013.txt\n");
        printf("5 - tsp5_27603.txt\n");
        printf("0 - sair\n\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            nome_arquivo = "../docs/tsp1_253.txt";
            otimo = 253;
            break;

        case 2:
            nome_arquivo = "../docs/tsp2_1248.txt";
            otimo = 1248;
            break;

        case 3:
            nome_arquivo = "../docs/tsp3_1194.txt";
            otimo = 1194;
            break;

        case 4:
            nome_arquivo = "../docs/tsp4_7013.txt";
            otimo = 7013;
            break;

        case 5:
            nome_arquivo = "../docs/tsp5_27603.txt";
            otimo = 27603;
            break;

        case 0:
            exit(0);
        }

    } while (opcao < 0 || opcao > 5);

    int **matriz = ler_arquivo(nome_arquivo, &numeros_vc);

    int visitados[numeros_vc];

    for (int i = 0; i < numeros_vc; i++)
    {
        visitados[i] = 0;
    }

    visitados[0] = 1;

    if (matriz == NULL)
    {
        printf("Erro de leitura.\n");
    }

    printf("Leitura concluida\n");
    printf("Tamanho da matriz: %d\n\n", numeros_vc);
    printf(".........................................\n");
    printf("Calculando algoritmo aproximativo...\n");

    clock_t inicio = clock();
    int resultado_aproximado = algoritmo_aproximativo(matriz, numeros_vc);
    clock_t fim = clock();
    double tempo_aproximativo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // cálculo de gap
    double gap_aproximativo;

    gap_aproximativo = ((double)(resultado_aproximado - otimo) / otimo) * 100;

    printf("Valor otimo: %d\n", otimo);
    printf("Custo e tempo com algortimo aproximado (respectivamente): %d, %f\n", resultado_aproximado, tempo_aproximativo);
    printf("Gap: %.2f%%\n", gap_aproximativo);
    printf(".........................................\n\n");

    printf("Calculando algoritmo forca bruta...\n");

    for (int i = 0; i < numeros_vc; i++)
    {
        visitados[i] = 0;
    }

    visitados[0] = 1;

    int estourou = 0;
    int limite_segundos = 10;

    clock_t inicioo = clock();
    int resultado_forca_bruta = algoritmo_forca_bruta(matriz, numeros_vc, 0, 0, 1, visitados, inicioo, limite_segundos, &estourou);
    clock_t fimm = clock();
    double tempo_forca_bruta = (double)(fimm - inicioo) / CLOCKS_PER_SEC;


    if(estourou==1){
        printf("\033[1;31m""Programa abortado: excedeu 10 segundos.\n""\033[0m");
    }
    // cálculo gap
    double gap_forca_bruta;

    gap_forca_bruta = ((double)(resultado_forca_bruta - otimo) / otimo) * 100;

    printf("Valor otimo: %d\n", otimo);
    printf("Custo e tempo com algortimo forca bruta (respectivamente): %d, %f\n", resultado_forca_bruta, tempo_forca_bruta);
    printf("Gap: %.2f%%\n", gap_forca_bruta);
    printf(".........................................\n");


    int op;

    printf("Impimir matriz selecionada?\n");
    printf("1 - sim\n");
    printf("2 - nao\n");
    scanf("%d", &op);

    if (op==2){
        return 0;
        free(matriz);
    }

    printf("Matriz:");

    for (int i = 0; i < numeros_vc; i++)
    {
        printf("\n");
        for (int j = 0; j < numeros_vc; j++)
        {
            printf("%d, ", matriz[i][j]);
        }
    }

    printf("\n");

    free(matriz);
    return 0;
}
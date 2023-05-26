#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

struct Produto
{
    int id;
    int weight;
    int weightAnt;
};

int gerarNumeroAleatorio(int min, int max)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}
int indiceMenorValor(int *vetor, int tamanho)
{
    int menor = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] < vetor[menor])
        {
            menor = i;
        }
    }
    return menor;
}

int indiceMaiorValor(int *vetor, int tamanho)
{
    int maior = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] > vetor[maior])
        {
            maior = i;
        }
    }
    return maior;
}

// Move um produto de uma linha para outra escolhida aleatoriamente
void vizinhanca1(int *solucao, int tamanho)
{
    // Seleciona duas linhas de produção aleatoriamente
    int linha1 = rand() % tamanho;
    int linha2;
    do
    {
        linha2 = rand() % tamanho;
    } while (linha1 == linha2);

    // Move um produto da linha1 para linha2
    if (solucao[linha1] > 0)
    {
        solucao[linha1] -= 1;
        solucao[linha2] += 1;
    }
}

// Troca a quantidade de produtos entre duas linhas escolhidas
void vizinhanca2(int *solucao, int tamanho)
{
    // Seleciona duas linhas de produção aleatoriamente
    int linha1 = rand() % tamanho;
    int linha2;
    do
    {
        linha2 = rand() % tamanho;
    } while (linha1 == linha2);

    // Troca a quantidade de produtos entre linha1 e linha2
    int temp = solucao[linha1];
    solucao[linha1] = solucao[linha2];
    solucao[linha2] = temp;
}

void SwapEntreLinhas(std::vector<std::vector<struct Produto>> &solucao, int tamanho, int *linhas, int *matriz, int numProdutos)
{
    // Seleciona duas linhas de produção aleatoriamente
    int linha1 = indiceMaiorValor(linhas, tamanho);
    int linha2 = indiceMenorValor(linhas, tamanho);

    int produto1 = gerarNumeroAleatorio(0, tamanho);
    int produto2 = gerarNumeroAleatorio(0, tamanho);

    struct Produto temp1, temp2;

    temp1 = solucao[linha1][produto1];
    temp2 = solucao[linha2][produto2];
    temp1.weightAnt = 0;
    temp2.weightAnt = 0;

    if (solucao[linha2][produto2].weightAnt != 0)
    {
        temp1.weightAnt = matriz[linha2 * numProdutos + temp1.id];
    }
    if (solucao[linha1][produto1].weightAnt != 0)
    {
        temp2.weightAnt = matriz[linha1 * numProdutos + temp2.id];
    }

    solucao[linha1][produto1] =temp2;
    solucao[linha2][produto2] =temp1;
    
    for (int i = 0; i < tamanho; i++)
    {
        linhas[i] =0;
    }
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < solucao[i].size(); j++)
        {
            linhas[i] += solucao[i][j].weight + solucao[i][j].weightAnt;
        }
    }
}

int main()
{
    int numLinhasProducao, numProdutos;
    std::ifstream inputFile("guloso.txt"); // Nome do arquivo de entrada

    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    inputFile >> numLinhasProducao >> numProdutos;

    std::cout << "Numero de linhas de producao " << numLinhasProducao << std::endl;
    std::cout << "Numero de produto " << numProdutos << std::endl;

    std::vector<std::vector<struct Produto>> solucao(numLinhasProducao);
    int linhas[numLinhasProducao];
    int produtos[numProdutos];
    int matrizProd[numProdutos][numProdutos];

    // Leitura das horas de cada Produto
    for (int i = 0; i < numProdutos; i++)
    {
        inputFile >> produtos[i];
    }

    // Montagem da Matriz
    for (int i = 0; i < numProdutos; i++)
    {
        for (int j = 0; j < numProdutos; j++)
        {
            inputFile >> matrizProd[i][j];
        }
    }

    inputFile.close();

    // Inicializando todas a Linhas com 0 horas
    for (int i = 0; i < numLinhasProducao; i++)
    {
        linhas[i] = 0;
    }

    for (int i = 0; i < numProdutos; i++)
    {

        // Retona o indice da fila com menor quantidade de horas
        int indiceFila = indiceMenorValor(linhas, numLinhasProducao);

        struct Produto novoProduto;
        novoProduto.id = i;
        novoProduto.weight = produtos[i];
        novoProduto.weightAnt = 0;

        if (solucao[indiceFila].size() != 0)
        {
            // Acessando o id do produto anterior e do atual, para acessar a relação de horas entre eles
            novoProduto.weightAnt = matrizProd[solucao[indiceFila][solucao[indiceFila].size() - 1].id][novoProduto.id];
        }
        linhas[indiceFila] += produtos[i] + novoProduto.weightAnt;
        // Atualização da quantidade horas na linha de produção
        solucao[indiceFila].push_back(novoProduto);
    }

    for (int i = 0; i < solucao.size(); i++)
    {
        std::cout << "Linha " << i << " --> ";
        for (int j = 0; j < solucao[i].size(); j++)
        {
            std::cout << "P[" << solucao[i][j].id << "] W[" << solucao[i][j].weight << "]  "
                      << "A[" << solucao[i][j].weightAnt << "]  ";
        }
        std::cout << std::endl;
    }
    int HorasGastas = linhas[indiceMaiorValor(linhas, numLinhasProducao)];
    std::cout << "Solucao Final " << HorasGastas << std::endl;

    SwapEntreLinhas(solucao, numLinhasProducao, linhas, &matrizProd[0][0], numProdutos);

    for (int i = 0; i < solucao.size(); i++)
    {
        std::cout << "Linha " << i << " --> ";
        for (int j = 0; j < solucao[i].size(); j++)
        {
            std::cout << "P[" << solucao[i][j].id << "] W[" << solucao[i][j].weight << "]  "
                      << "A[" << solucao[i][j].weightAnt << "]  ";
        }
        std::cout << std::endl;
    }

     HorasGastas = linhas[indiceMaiorValor(linhas, numLinhasProducao)];
    std::cout << "Solucao Final  Com  vizinhanca " << HorasGastas << std::endl;

    // for (int i = 0; i < 100; i++)
    // {
    //     int solucaoAnterior = solucao[indiceMaiorValor(solucao, numLinhasProducao)];

    //     // Escolhendo aleatoriamente um movimento de vizinhança
    //     if (rand() % 2 == 0)
    //         vizinhanca1(solucao, numLinhasProducao);
    //     else
    //         vizinhanca2(solucao, numLinhasProducao);

    //     int novaSolucao = solucao[indiceMaiorValor(solucao, numLinhasProducao)];

    //     // Se a nova solução é pior, revertemos a mudança
    //     if (novaSolucao > solucaoAnterior)
    //     {
    //         for (int i = 0; i < numLinhasProducao; i++)
    //         {
    //             solucao[i] = 0;
    //         }
    //         for (int i = 0; i < numProdutos; i++)
    //         {
    //             int indiceFila = indiceMenorValor(solucao, numLinhasProducao);
    //             solucao[indiceFila] += produtos[i];
    //         }
    //     }

    //     // atualize melhorSolucao quando uma melhor solução é encontrada:
    //     if (novaSolucao < melhorSolucao)
    //     {
    //         melhorSolucao = novaSolucao;
    //     }

    //     std::cout << "Solucao[" << i << "] = " << novaSolucao << ", com movimentos de vizinhanca" << std::endl;
    // }

    // int maior = indiceMaiorValor(solucao, numLinhasProducao);
    // std::cout << "Solucao sem movimentos de vizinhanca: " << solucao[maior] << std::endl;

    // std::cout << "Melhor Solucao com movimentos de vizinhanca: " << melhorSolucao << std::endl;

    return 0;
}
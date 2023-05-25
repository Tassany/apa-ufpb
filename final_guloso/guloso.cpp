#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

int main()
{
    int numLinhasProducao, numProdutos;
    std::ifstream inputFile("n10m2_A.txt"); // Nome do arquivo de entrada

    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    inputFile >> numLinhasProducao >> numProdutos;

    std::cout << "Numero de linhas de producao: " << numLinhasProducao << std::endl;
    std::cout << "Numero de produtos: " << numProdutos << std::endl;

    int solucao[numLinhasProducao];

    for (int i = 0; i < numLinhasProducao; i++)
    {
        solucao[i] = 0;
    }

    // ler um array do tamanho do numero de produtos
    int produtos[numProdutos];

    for (int i = 0; i < numProdutos; i++)
    {
        inputFile >> produtos[i];
    }

    inputFile.close();

    std::cout << "Produtos: ";
    for (int i = 0; i < numProdutos; i++)
    {
        std::cout << produtos[i] << " ";
    }
    std::cout << std::endl;

    // Vetor de vetores para armazenar os produtos em cada linha de produção
    std::vector<std::vector<int>> linhaProducao(numLinhasProducao);

    for (int i = 0; i < numProdutos; i++)
    {
        int indiceFila = indiceMenorValor(solucao, numLinhasProducao);
        solucao[indiceFila] += produtos[i];

        // Adiciona o produto na linha de produção correspondente
        linhaProducao[indiceFila].push_back(produtos[i]);
    }

    int maior = indiceMaiorValor(solucao, numLinhasProducao);
    std::cout << "Solucao sem movimentos de vizinhanca: " << solucao[maior] << std::endl;

    // Imprime os produtos em cada linha de produção
    for (int i = 0; i < numLinhasProducao; i++)
    {
        std::cout << "Produtos na linha " << i + 1 << ":\t";
        for (int j = 0; j < linhaProducao[i].size(); j++)
        {
            std::cout << linhaProducao[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
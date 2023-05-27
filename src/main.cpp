#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "./utils/Util.h"
#include "./vizinhancas/Vizinhanca.h"
#include "./algoritmos/Algoritmo.h"

int main()
{
    Util utils;
    Vizinhanca viz;
    Algoritmo alg;
    int numLinhasProducao, numProdutos;
    //std::ifstream inputFile("./instancias/n10m2_A.txt"); // Nome do arquivo de entrada
    std::ifstream inputFile("./src/guloso.txt");
    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    inputFile >> numLinhasProducao >> numProdutos;

    std::cout << "Numero de linhas de producao " << numLinhasProducao << std::endl;
    std::cout << "Numero de produto " << numProdutos << std::endl;
    
    std::vector<std::vector<Vizinhanca::Produto>> solucao(numLinhasProducao);
    int linhas[numLinhasProducao];
    int produtos[numProdutos];
    int *matrizProd = (int *)malloc(numProdutos * numProdutos * sizeof(int));
    // int *matriz = (int *)malloc(linhas * colunas * sizeof(int));

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
            inputFile >> matrizProd[i * numProdutos + j];
        }
    }

    inputFile.close();

    alg.guloso(solucao,linhas, numLinhasProducao, numProdutos, matrizProd, produtos);
    
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
    int HorasGastas = linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)];
    std::cout << "Solucao Final " << HorasGastas << std::endl;

    
    viz.swapEntreLinhas(solucao, numLinhasProducao, linhas, matrizProd, numProdutos);

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

    HorasGastas = linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)];
    std::cout << "Solucao Final  Com  vizinhanca " << HorasGastas << std::endl;

    viz.swapEmUmaUnicaLinha(solucao, numLinhasProducao, linhas, matrizProd, numProdutos);

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

    HorasGastas = linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)];
    std::cout << "Solucao Final  Com  vizinhanca  2 " << HorasGastas << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "./utils/Util.h"
#include "./vizinhancas/Vizinhanca.h"
#include "./algoritmos/Algoritmo.h"
#include "./metaHeuristica/ILS.h"
#include "./busca/VND.h"
#include "./metaHeuristica/ILS.h"

int main()
{
    // Obtém o tempo de início
    auto start = std::chrono::high_resolution_clock::now();

    Util utils;
    Vizinhanca viz;
    Algoritmo alg;
    VND vnd;
    int numLinhasProducao, numProdutos;

    // std::ifstream inputFile("./instancias/n40m5_A.txt"); // Nome do arquivo de entrada
    std::ifstream inputFile("./src/guloso.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    inputFile >> numLinhasProducao >> numProdutos;

    std::vector<std::vector<Vizinhanca::Produto>> solucao(numLinhasProducao);
    std::vector<int> linhas(numLinhasProducao);
    int produtos[numProdutos];
    int *matrizProd = (int *)malloc(numProdutos * numProdutos * sizeof(int));

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

    alg.guloso(solucao, linhas, numLinhasProducao, numProdutos, matrizProd, produtos);

    int HorasGastas = linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)];

    // Apenas o Guloso - Inicio -----------------------------------------------
    for (int i = 0; i < solucao.size(); i++)
    {
        std::cout << "Linha " << i << " --> ";
        for (int j = 0; j < solucao[i].size(); j++)
        {
            std::cout << "P[" << solucao[i][j].id << "] W[" << solucao[i][j].weight << "]  "
                      << "A[" << solucao[i][j].weightAnt << "] | ";
        }
        std::cout << std::endl;
    }

    std::cout << "Solucao Final  Sem Vizinhanca " << HorasGastas << std::endl;
    // Apenas o Guloso - Fim -------------------------------------------------

    // VND - Inicio  ----------------------------------------------------------------

    // std::vector<std::vector<Vizinhanca::Produto>> melhorSolucao(solucao);
    // std::vector<int> Melhorlinhas(linhas);

    // vnd.run(melhorSolucao, Melhorlinhas, solucao, linhas, numLinhasProducao, matrizProd, numProdutos);

    // for (int i = 0; i < melhorSolucao.size(); i++)
    // {
    //     std::cout << "Linha " << i << " --> ";
    //     for (int j = 0; j < melhorSolucao[i].size(); j++)
    //     {
    //         std::cout << "P[" << melhorSolucao[i][j].id << "] W[" << melhorSolucao[i][j].weight << "]  "
    //                   << "A[" << melhorSolucao[i][j].weightAnt << "]  ";
    //     }
    //     std::cout << std::endl;
    // }

    // HorasGastas = Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)];
    // std::cout << "Solucao Final  Com  vizinhanca " << HorasGastas << std::endl;

    // VND - Fim  ----------------------------------------------------------------

    // Obtém o tempo de término
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a duração em segundos
    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    std::cout << "Tempo de execução: " << seconds << " segundos." << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include "./utils/Util.h"
#include "./vizinhancas/Vizinhanca.h"
#include "./algoritmos/Algoritmo.h"

int main()
{
    Util utils;
    Vizinhanca viz;
    std::vector<Vizinhanca::ElementosSelecionados> selecao;
    Algoritmo alg;
    int numLinhasProducao, numProdutos;
    std::ifstream inputFile("./instancias/n10m2_B.txt"); // Nome do arquivo de entrada
    //std::ifstream inputFile("./src/guloso.txt");
    //  Verifica se o arquivo foi aberto corretamente
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

    alg.guloso(solucao, linhas, numLinhasProducao, numProdutos, matrizProd, produtos);

   
    int HorasGastas = linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)];


    // VND
    std::vector<std::vector<Vizinhanca::Produto>> melhorSolucao(solucao);
    std::vector<int> Melhorlinhas(linhas);
    std::vector<std::vector<Vizinhanca::Produto>> tempSolucao(solucao);
    std::vector<int> tempLinhas(linhas);
    int numeroPossibilidadesViz1 = solucao[utils.indiceMaiorValor(linhas, numLinhasProducao)].size() * solucao[utils.indiceMenorValor(linhas, numLinhasProducao)].size();
    int numeroPossibilidadesViz2 = (solucao[utils.indiceMaiorValor(linhas, numLinhasProducao)].size() * (solucao[utils.indiceMaiorValor(linhas, numLinhasProducao)].size() - 1)) / 2;
    int vizinhanca = 1;
    bool buscar = true;

    while (buscar)
    {

        switch (vizinhanca)
        {

        case 1:
            while (selecao.size() < numeroPossibilidadesViz1)
            {

                Vizinhanca::ElementosSelecionados opcao = viz.swapEntreLinhas(solucao, numLinhasProducao, linhas, matrizProd, numProdutos);

                auto it = std::find_if(selecao.begin(), selecao.end(), [&](const Vizinhanca::ElementosSelecionados &selecao)
                                       { return selecao.linha1 == opcao.linha1 && selecao.linha2 == opcao.linha2 && selecao.prod1 == opcao.prod1 && selecao.prod2 == opcao.prod2;; });

                if (it == selecao.end())
                {
                    selecao.push_back(opcao);
                }
                if (linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)] < Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)])
                {
                    melhorSolucao = solucao;
                    Melhorlinhas = linhas;
                }

                solucao = tempSolucao;
                linhas = tempLinhas;
            }
            selecao.clear();

        case 2:
            while (selecao.size() < numeroPossibilidadesViz2)
            {

                Vizinhanca::ElementosSelecionados opcao = viz.swapEmUmaUnicaLinha(solucao, numLinhasProducao, linhas, matrizProd, numProdutos);

                auto it = std::find_if(selecao.begin(), selecao.end(), [&](const Vizinhanca::ElementosSelecionados &selecao)
                                       { return selecao.linha1 == opcao.linha1 && selecao.linha2 == opcao.linha2 && selecao.prod1 == opcao.prod1 && selecao.prod2 == opcao.prod2;; });

                if (it == selecao.end())
                {
                   
                    selecao.push_back(opcao);
                }
                if (linhas[utils.indiceMaiorValor(linhas, numLinhasProducao)] < Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)])
                {
                    melhorSolucao = solucao;
                    Melhorlinhas = linhas;
                }
                solucao = tempSolucao;
                linhas = tempLinhas;
            }
            selecao.clear();
        }

        if (Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)] < tempLinhas[utils.indiceMaiorValor(tempLinhas, numLinhasProducao)])
        {
           

            HorasGastas = tempLinhas[utils.indiceMaiorValor(tempLinhas, numLinhasProducao)];
           
            HorasGastas = Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)];
           
            solucao = melhorSolucao;
            linhas = Melhorlinhas;
            tempSolucao = melhorSolucao;
            tempLinhas = Melhorlinhas;
        }
        else
        {
            buscar = false;
        }
    }

    std::cout << "Melhor " << std::endl;
    for (int i = 0; i < melhorSolucao.size(); i++)
    {
        std::cout << "Linha " << i << " --> ";
        for (int j = 0; j < melhorSolucao[i].size(); j++)
        {
            std::cout << "P[" << melhorSolucao[i][j].id << "] W[" << melhorSolucao[i][j].weight << "]  "
                      << "A[" << melhorSolucao[i][j].weightAnt << "]  ";
        }
        std::cout << std::endl;
    }

    HorasGastas = Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)];
    std::cout << "Solucao Final  Com  vizinhanca " << HorasGastas << std::endl;

    return 0;
}
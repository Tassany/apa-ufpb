#include <iostream>
#include <vector>
#include <algorithm>
#include "Algoritmo.h"
#include "../utils/Util.h"
#include "../vizinhancas/Vizinhanca.h"

void Algoritmo::guloso(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int *linhas, int numLinhasProducao, int numProdutos, int *matrizProd, int *produtos)
{
    Util utils;
    for (int i = 0; i < numLinhasProducao; i++)
    {
        linhas[i] = 0;
    }
    for (int i = 0; i < numProdutos; i++)
    {
        for (int j = 0; j < numProdutos; j++)
        {
            std::cout << matrizProd[i * numProdutos + j] << " --> ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numProdutos; i++)
    {

        // Retona o indice da fila com menor quantidade de horas
        int indiceFila = utils.indiceMenorValor(linhas, numLinhasProducao);

        Vizinhanca::Produto novoProduto;
        novoProduto.id = i;
        novoProduto.weight = produtos[i];
        novoProduto.weightAnt = 0;

        if (solucao[indiceFila].size() != 0)
        {
            // Acessando o id do produto anterior e do atual, para acessar a relação de horas entre eles
            novoProduto.weightAnt = matrizProd[solucao[indiceFila][solucao[indiceFila].size() - 1].id * numProdutos + novoProduto.id];
        }
        linhas[indiceFila] += produtos[i] + novoProduto.weightAnt;
        // Atualização da quantidade horas na linha de produção
        solucao[indiceFila].push_back(novoProduto);
    }
}

void Algoritmo::vnd(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int *linhas, int numLinhasProducao, int numProdutos, int *matrizProd, int *produtos)
{
    
}

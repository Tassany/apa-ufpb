#include "Vizinhanca.h"
#include <iostream>
#include <vector>
#include "../utils/Util.h"
 
    Vizinhanca::Produto temp1, temp2;

void Vizinhanca::swapEmUmaUnicaLinha(std::vector<std::vector<Produto>> &solucao, int tamanho, int *linhas, int *matriz, int numProdutos)
{   
    Util utils;
    // Seleciona a linha de maior valor
    int linha1 = utils.indiceMaiorValor(linhas, tamanho);

    int produto1 = utils.gerarNumeroAleatorio(0, solucao[linha1].size() - 1);
    int produto2;
    do
    {
        produto2 = utils.gerarNumeroAleatorio(0, solucao[linha1].size() - 1);
    } while (produto1 == produto2);

    Vizinhanca:: Produto temp1, temp2;
    std::cout << "Prod 1 : " << produto1 << " Prod 2 : " << produto2 << std::endl;
    temp1 = solucao[linha1][produto1];
    std::cout << "Temp 1 : " << temp1.id << std::endl;
    temp2 = solucao[linha1][produto2];
    std::cout << "Temp 2 : " << temp2.id << std::endl;
    temp1.weightAnt = 0;
    temp2.weightAnt = 0;

    solucao[linha1][produto1] = temp2;
    solucao[linha1][produto2] = temp1;

    if (produto1)
    {
        solucao[linha1][produto1].weightAnt = matriz[solucao[linha1][produto1 - 1].id * numProdutos + solucao[linha1][produto1].id];
    }
    if (produto2)
    {
        std::cout << "Matriz 2 : " << solucao[linha1][produto2 - 1].id << " " << solucao[linha1][produto2].id << std::endl;
        solucao[linha1][produto2].weightAnt = matriz[solucao[linha1][produto2 - 1].id * numProdutos + solucao[linha1][produto2].id];
    }
    if (solucao[linha1].size() - 1 != produto1)
    {
        solucao[linha1][produto1 + 1].weightAnt = matriz[solucao[linha1][produto1].id * numProdutos + solucao[linha1][produto1 + 1].id];
    }
    if (solucao[linha1].size() - 1 != produto2)
    {
        solucao[linha1][produto2 + 1].weightAnt = matriz[solucao[linha1][produto2].id * numProdutos + solucao[linha1][produto2 + 1].id];
    }

    linhas[linha1] = 0;
    for (int j = 0; j < solucao[linha1].size(); j++)
    {
        linhas[linha1] += solucao[linha1][j].weight + solucao[linha1][j].weightAnt;
    }
}
void Vizinhanca::swapEntreLinhas(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int tamanho, int *linhas, int *matriz, int numProdutos)
{
    Util utils;
    // Seleciona duas linhas de produção aleatoriamente
    int linha1 = utils.indiceMaiorValor(linhas, tamanho);
    int linha2 = utils.indiceMenorValor(linhas, tamanho);

    int produto1 = utils.gerarNumeroAleatorio(0, solucao[linha1].size() - 1);
    int produto2 = utils.gerarNumeroAleatorio(0, solucao[linha2].size() - 1);

    struct Produto temp1, temp2;
    std::cout << "Prod 1 : " << produto1 << " Prod 2 : " << produto2 << std::endl;
    temp1 = solucao[linha1][produto1];
    std::cout << "Temp 1 : " << temp1.id << std::endl;
    temp2 = solucao[linha2][produto2];
    std::cout << "Temp 2 : " << temp2.id << std::endl;
    temp1.weightAnt = 0;
    temp2.weightAnt = 0;

    if (solucao[linha2][produto2].weightAnt != 0)
    {
        temp1.weightAnt = matriz[solucao[linha2][produto2 - 1].id * numProdutos + temp1.id];
    }
    if (solucao[linha2].size() - 1 != produto2)
    {
        solucao[linha2][produto2 + 1].weightAnt = matriz[temp1.id * numProdutos + solucao[linha2][produto2 + 1].id];
    }
    if (solucao[linha1][produto1].weightAnt != 0)
    {
        temp2.weightAnt = matriz[solucao[linha1][produto1 - 1].id * numProdutos + temp2.id];
    }
    if (solucao[linha1].size() - 1 != produto1)
    {
        solucao[linha1][produto1 + 1].weightAnt = matriz[temp2.id * numProdutos + solucao[linha1][produto1 + 1].id];
    }
    solucao[linha1][produto1] = temp2;
    solucao[linha2][produto2] = temp1;

    for (int i = 0; i < tamanho; i++)
    {
        linhas[i] = 0;
    }
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < solucao[i].size(); j++)
        {
            linhas[i] += solucao[i][j].weight + solucao[i][j].weightAnt;
        }
    }
}
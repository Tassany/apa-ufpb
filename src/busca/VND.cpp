#include "VND.h"
#include <vector>

void VND::run(std::vector<std::vector<Vizinhanca::Produto>> &melhorSolucao, std::vector<int> &Melhorlinhas, std::vector<std::vector<Vizinhanca::Produto>> &solucao, std::vector<int> &linhas, int numLinhasProducao, int *matrizProd, int numProdutos)
{
    Util utils;
    std::vector<Vizinhanca::ElementosSelecionados> selecao;
    Vizinhanca viz;
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
                                       { return selecao.linha1 == opcao.linha1 && selecao.linha2 == opcao.linha2 && selecao.prod1 == opcao.prod1 && selecao.prod2 == opcao.prod2; });

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
            break;

        case 2:
            while (selecao.size() < numeroPossibilidadesViz2)
            {
                Vizinhanca::ElementosSelecionados opcao = viz.swapEmUmaUnicaLinha(solucao, numLinhasProducao, linhas, matrizProd, numProdutos);

                auto it = std::find_if(selecao.begin(), selecao.end(), [&](const Vizinhanca::ElementosSelecionados &selecao)
                                       { return selecao.linha1 == opcao.linha1 && selecao.linha2 == opcao.linha2 && selecao.prod1 == opcao.prod1 && selecao.prod2 == opcao.prod2; });

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
            break;
        }

        if (Melhorlinhas[utils.indiceMaiorValor(Melhorlinhas, numLinhasProducao)] < tempLinhas[utils.indiceMaiorValor(tempLinhas, numLinhasProducao)])
        {
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
}

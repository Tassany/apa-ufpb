#include "ILS.h"
#include "../vizinhancas/Vizinhanca.h"
#include "../busca/VND.h"

// Função principal da ILS
std::vector<std::vector<int>> ils(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int numIteracoes)
{
    srand(time(nullptr)); // Inicializa a semente do gerador de números aleatórios

    for (int i = 0; i < numIteracoes; ++i)
    {
        std::vector<std::vector<int>> candidateSolution = currentSolution; // Perturbação: a solução candidata é uma cópia da solução atual
        candidateSolution = localSearch(candidateSolution);                // Realiza a busca local na solução candidata

        if (objectiveFunction(candidateSolution) < objectiveFunction(currentSolution))
        {
            currentSolution = candidateSolution; // Atualiza a solução atual se a nova solução for melhor
        }
    }

    return currentSolution;
}
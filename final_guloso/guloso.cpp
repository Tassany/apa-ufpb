#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

int indiceMenorValor(int *vetor, int tamanho){
    int menor = 0;
    for(int i =0; i < tamanho; i++){
        if(vetor[i]<vetor[menor]){
            menor =i;
        }
    }
    return menor;
}

int indiceMaiorValor(int *vetor, int tamanho){
    int maior = 0;

    for(int i =0; i < tamanho; i++){
        if(vetor[i]>vetor[maior]){
            maior =i;
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

int main()
{
    int numLinhasProducao, numProdutos;
    std::ifstream inputFile("n500m10_A.txt"); // Nome do arquivo de entrada

    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    inputFile >> numLinhasProducao >> numProdutos;

    std::cout << "Numero de linhas de producao "<< numLinhasProducao << std::endl;
    std::cout << "Numero de produto "<< numProdutos << std::endl;

    int solucao[numLinhasProducao] ;
    int melhorSolucao = INT_MAX;

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

    std::cout << "Produto ";
    for(int i = 0; i< numProdutos; i++){
            std::cout << produtos[i] << " ";
        }
        std::cout << std::endl;
    for(int i = 0; i< numProdutos; i++){
        int indiceFila = indiceMenorValor(solucao, numLinhasProducao);
        solucao[indiceFila] += produtos[i];
        std::cout << "Linhas de Producao ";
        for(int i = 0; i< numLinhasProducao; i++){
            std::cout << solucao[i] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 100; i++)
    {
        int solucaoAnterior = solucao[indiceMaiorValor(solucao, numLinhasProducao)];

        // Escolhendo aleatoriamente um movimento de vizinhança
        if (rand() % 2 == 0)
            vizinhanca1(solucao, numLinhasProducao);
        else
            vizinhanca2(solucao, numLinhasProducao);

        int novaSolucao = solucao[indiceMaiorValor(solucao, numLinhasProducao)];

        // Se a nova solução é pior, revertemos a mudança
        if (novaSolucao > solucaoAnterior)
        {
            for (int i = 0; i < numLinhasProducao; i++)
            {
                solucao[i] = 0;
            }
            for (int i = 0; i < numProdutos; i++)
            {
                int indiceFila = indiceMenorValor(solucao, numLinhasProducao);
                solucao[indiceFila] += produtos[i];
            }
        }

        // atualize melhorSolucao quando uma melhor solução é encontrada:
        if (novaSolucao < melhorSolucao)
        {
            melhorSolucao = novaSolucao;
        }

        std::cout << "Solucao[" << i << "] = " << novaSolucao << ", com movimentos de vizinhanca" << std::endl;
    }

    int maior = indiceMaiorValor(solucao, numLinhasProducao);
    std::cout << "Solucao sem movimentos de vizinhanca: " << solucao[maior] << std::endl;

    std::cout << "Melhor Solucao com movimentos de vizinhanca: " << melhorSolucao << std::endl;

    return 0;
}
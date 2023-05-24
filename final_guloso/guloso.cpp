#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
   int maior = indiceMaiorValor(solucao, numLinhasProducao);
    std::cout << "Solucao " << solucao[maior]<< std::endl; ;

    return 0;
}
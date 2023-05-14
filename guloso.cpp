#include <iostream>
#include <fstream>
#include <vector>

// funcao gulosa valor por kg
std::vector<float> guloso(std::vector<float> peso, std::vector<float> valor, int capacidade)
{
    std::vector<float> valorPorKg;
    for (int i = 0; i < peso.size(); i++)
    {
        valorPorKg.push_back(valor[i] / peso[i]);
    }
    // Imprime o vetor de valores por kg
    std::cout << "\nVetor de valores por kg: ";
    for (int i = 0; i < valorPorKg.size(); i++)
    {
        std::cout << valorPorKg[i] << " ";
    }

    return valorPorKg;
}

int main()
{

    float pesoInt, valorInt;
    std::vector<float> peso, valor;
    std::string fileName = "arquivoGuloso.txt"; // Nome do arquivo a ser lido

    // Abre o arquivo
    std::ifstream inputFile(fileName);

    if (!inputFile)
    {
        std::cerr << "Erro ao abrir o arquivo " << fileName << std::endl;
        return 1;
    }

    // Lê os valores do arquivo e imprime como peso e valor
    while (inputFile >> pesoInt >> valorInt)
    {
        peso.push_back(pesoInt);
        valor.push_back(valorInt);
    }

    // Imprime o vetor de pesos
    std::cout << "Vetor de pesos: ";
    for (int i = 0; i < peso.size(); i++)
    {
        std::cout << peso[i] << " ";
    }

    // Imprime o vetor de valores
    std::cout << "\nVetor de valores: ";
    for (int i = 0; i < valor.size(); i++)
    {
        std::cout << valor[i] << " ";
    }

    std::cout << std::endl;

    guloso(peso, valor, 15);
    // Fecha o arquivo
    inputFile.close();

    return 0;
}
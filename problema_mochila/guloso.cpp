#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Item
{
    int peso;
    int valor;
};

bool compararPorTaxa(Item a, Item b)
{
    double taxaA = static_cast<double>(a.valor) / a.peso;
    double taxaB = static_cast<double>(b.valor) / b.peso;
    return taxaA > taxaB;
}
// funcao gulosa valor por kg
double mochilaGulosa(std::vector<Item> &itens, int capacidade)
{
    std::sort(itens.begin(), itens.end(), compararPorTaxa);

    double valorTotal = 0.0;
    int pesoAtual = 0;

    for (const auto &item : itens)
    {
        if (pesoAtual + item.peso <= capacidade)
        {
            valorTotal += item.valor;
            pesoAtual += item.peso;
        }
        // verifica a proporcao do item atual que pode ser colocado na mochila
        // else
        // {
        //     double proporcao = static_cast<double>(capacidade - pesoAtual) / item.peso;
        //     valorTotal += proporcao * item.valor;
        //     break;
        // }
    }

    return valorTotal;
}

int main()
{
    std::string fileName = "arquivoGuloso.txt"; // Nome do arquivo a ser lido

    // Abre o arquivo
    std::ifstream inputFile(fileName);

    if (!inputFile)
    {
        std::cerr << "Erro ao abrir o arquivo " << fileName << std::endl;
        return 1;
    }

    std::vector<Item> itens;
    Item item;

    // Lê os valores do arquivo e armazena na struct
    while (inputFile >> item.peso >> item.valor)
    {
        itens.push_back(item);
    }

    // Fecha o arquivo
    inputFile.close();

    double valorMochila = mochilaGulosa(itens, 35);

    std::cout << "Valor total da mochila: " << valorMochila << std::endl;

    return 0;
}
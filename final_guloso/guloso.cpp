#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Edge
{
    int source;
    int destination;
    int weight;
};

bool compareEdges(const Edge &edge1, const Edge &edge2)
{
    return edge1.weight < edge2.weight;
}

int main()
{
    std::ifstream inputFile("guloso.txt"); // Nome do arquivo de entrada

    // Verifica se o arquivo foi aberto corretamente
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Lê a matriz do arquivo
    std::vector<Edge> edges;
    int valor;
    int numLinhasProducao, numProdutos;

    inputFile >> numLinhasProducao >> numProdutos;

    // ler um array do tamanho do numero de produtos
    int *produtos = new int[numProdutos];

    for (int i = 0; i < numProdutos; i++)
    {
        inputFile >> produtos[i];
    }

    for (int i = 0; i < numProdutos; i++)
    {
        for (int j = 0; j < numProdutos; j++)
        {
            inputFile >> valor;
            if (valor != 0)
            {
                Edge edge;
                edge.source = i;
                edge.destination = j;
                edge.weight = valor;
                edges.push_back(edge);
            }
        }
    }

    inputFile.close();

    // Ordena os edges pelo peso em ordem crescente
    std::sort(edges.begin(), edges.end(), compareEdges);

    // Imprime as arestas ordenadas
    for (const auto &edge : edges)
    {
        std::cout << "Origem: " << edge.source + 1 << ", Destino: " << edge.destination + 1 << ", Peso: " << edge.weight << std::endl;
    }

    return 0;
}
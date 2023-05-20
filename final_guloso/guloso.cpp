#include <iostream>
#include <fstream>
#include <vector>

struct Edge
{
    int i;    // Origem
    int j;    // Destino
    int peso; // Peso
};

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

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            inputFile >> valor;
            if (valor != 0)
            {
                Edge edge;
                edge.i = i;
                edge.j = j;
                edge.peso = valor;
                edges.push_back(edge);
            }
        }
    }

    inputFile.close();

    // Imprime as arestas lidas
    for (const auto &edge : edges)
    {
        std::cout << "Origem: " << edge.i << ", Destino: " << edge.j << ", Peso: " << edge.peso << std::endl;
    }

    return 0;
}
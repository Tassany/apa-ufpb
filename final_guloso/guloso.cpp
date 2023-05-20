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

class DisjointSet
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);

        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
        {
            return;
        }

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};
bool compareEdges(const Edge &edge1, const Edge &edge2)
{
    return edge1.weight < edge2.weight;
}

std::vector<Edge> kruskalMST(const std::vector<Edge> &edges, int numVertices)
{
    std::vector<Edge> mst;
    DisjointSet ds(numVertices);

    // Ordena as arestas pelo peso em ordem crescente
    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), compareEdges);

    for (const auto &edge : sortedEdges)
    {
        int sourceRoot = ds.find(edge.source);
        int destRoot = ds.find(edge.destination);

        // Verifica se a aresta forma um ciclo ou se a origem ou destino já foram utilizados
        if (sourceRoot != destRoot && sourceRoot != edge.destination && destRoot != edge.source)
        {
            mst.push_back(edge);
            ds.unite(sourceRoot, destRoot);
        }
    }

    return mst;
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

    // Ordena os edges em ordem crescente de peso
    std::vector<Edge> mst = kruskalMST(edges, numProdutos);

    // Imprime as arestas lidas
    // for (const auto &edge : edges)
    // {
    //     std::cout << "Origem: " << edge.source + 1 << ", Destino: " << edge.destination + 1 << ", Peso: " << edge.weight << std::endl;
    // }

    std::cout << "Arestas da MST:" << std::endl;
    for (const auto &edge : mst)
    {
        std::cout << edge.source + 1 << " - " << edge.destination + 1 << " : " << edge.weight << std::endl;
    }

    return 0;
}
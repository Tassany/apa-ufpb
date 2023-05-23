#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int source;
    int destination;
    int weight;

    Edge(int src, int dst, int w) : source(src), destination(dst), weight(w) {}
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

std::vector<std::vector<Edge>> kruskalMST(const std::vector<Edge> &edges, int numVertices)
{
    std::vector<std::vector<Edge>> solutions;
    DisjointSet ds(numVertices);

    // Ordena as arestas pelo peso em ordem crescente
    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), compareEdges);

    int numNodes = 0;
    int currentSolution = 0;

    solutions.push_back(std::vector<Edge>());

    for (const auto &edge : sortedEdges)
    {
        int sourceRoot = ds.find(edge.source);
        int destRoot = ds.find(edge.destination);

        // Verifica se a aresta forma um ciclo ou se a origem ou destino já foram utilizados
        if (sourceRoot != destRoot && sourceRoot != edge.destination && destRoot != edge.source)
        {
            solutions[currentSolution].push_back(edge);
            ds.unite(sourceRoot, destRoot);
            numNodes++;

            // Verifica se a solução atual atingiu a metade do número de vértices
            if (numNodes == numVertices / 2 && currentSolution < 1)
            {
                currentSolution++;
                solutions.push_back(std::vector<Edge>());
                numNodes = 0;
            }
        }
    }

    return solutions;
}

int main()
{
    int numVertices = 8;
    std::vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 2},
        {0, 3, 1},
        {1, 2, 3},
        {1, 4, 6},
        {2, 3, 2},
        {2, 5, 5},
        {3, 6, 4},
        {4, 5, 7},
        {4, 7, 3},
        {5, 6, 1},
        {5, 7, 2}};

    std::vector<std::vector<Edge>> msts = kruskalMST(edges, numVertices);

    // Imprime as duas árvores geradoras mínimas (MSTs)
    for (int i = 0; i < msts.size(); i++)
    {
        std::cout << "Arestas da MST " << (i + 1) << ":" << std::endl;
        for (const auto &edge : msts[i])
        {
            std::cout << edge.source << " - " << edge.destination << " : " << edge.weight << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}

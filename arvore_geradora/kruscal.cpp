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
    int numVertices = 6;
    std::vector<Edge> edges = {
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
        {1, 2, 5},
        {1, 4, 7},
        {2, 3, 4},
        {2, 4, 8},
        {3, 4, 6},
        {3, 5, 2},
        {4, 5, 1}};

    std::vector<Edge> mst = kruskalMST(edges, numVertices);

    // Imprime a árvore geradora mínima (MST)
    std::cout << "Arestas da MST:" << std::endl;
    for (const auto &edge : mst)
    {
        std::cout << edge.source << " - " << edge.destination << " : " << edge.weight << std::endl;
    }

    return 0;
}

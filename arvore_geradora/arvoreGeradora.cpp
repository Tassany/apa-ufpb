// OBJETIVO: minimizar a soma dos pesos das arestas(custo) de uma arvore geradora

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Aresta
{
    int origem;
    int destino;
    int peso;
};

// Função de comparação para ordenar as arestas pelo peso
bool compararArestas(const Aresta &a1, const Aresta &a2)
{
    return a1.peso < a2.peso;
}

int Kruskal(std::vector<Aresta> &arestas)
{
    sort(arestas.begin(), arestas.end(), compararArestas);
}

int main()
{

    return 0;
}
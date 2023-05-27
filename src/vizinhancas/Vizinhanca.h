#ifndef Vizinhanca_H
#define Vizinhanca_H
#include <random>
#include <vector>

class Vizinhanca
{
private:
 

public:
 struct Produto
    {
        int id;
        int weight;
        int weightAnt;
    };
    
    void swapEntreLinhas(std::vector<std::vector<Produto>> &solucao, int tamanho, int *linhas, int *matriz, int numProdutos);
    void swapEmUmaUnicaLinha(std::vector<std::vector<Produto>> &solucao, int tamanho, int *linhas, int *matriz, int numProdutos);
};

#endif

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
    struct ElementosSelecionados
    {
        int linha1;
        int linha2;
        int prod1;
        int prod2;
    };
    
    ElementosSelecionados swapEntreLinhas(std::vector<std::vector<Produto>> &solucao, int tamanho, std::vector<int> &linhas, int *matriz, int numProdutos);
    ElementosSelecionados swapEmUmaUnicaLinha(std::vector<std::vector<Produto>> &solucao, int tamanho, std::vector<int> &linhas, int *matriz, int numProdutos);
};

#endif

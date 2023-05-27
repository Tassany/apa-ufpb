#ifndef Algoritmo_H
#define Algoritmo_H
#include <random>
#include <vector>
#include "../vizinhancas/Vizinhanca.h"

class Algoritmo
{
private:
    struct Solucoes
    {
        int linha1;
        int linha2;
        int produto1;
        int produto2;
    };

    
public:
    struct MelhorSolucao
    {
        std::vector<std::vector<Vizinhanca::Produto>> solucaos;
        int linhas[];
    };
    void guloso(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int *linhas, int numLinhasProducao, int numProdutos, int *matrizProd, int *produtos);
    
    void vnd(std::vector<std::vector<Vizinhanca::Produto>> &solucao, int *linhas, int numLinhasProducao, int numProdutos, int *matrizProd, int *produtos);
};

#endif


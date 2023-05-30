#ifndef ILS_H
#define ILS_H
#include <vector>
#include <algorithm>
#include "../vizinhancas/Vizinhanca.h"
#include "../utils/Util.h"
class ILS
{
private:
public:
    void run(std::vector<std::vector<Vizinhanca::Produto>> &melhorSolucao, int numIteracoes, std::vector<int> &Melhorlinhas, std::vector<std::vector<Vizinhanca::Produto>> &solucao, std::vector<int> &linhas, int numLinhasProducao, int *matrizProd, int numProdutos);
};

#endif

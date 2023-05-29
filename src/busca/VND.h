#ifndef VND_H
#define VND_H

#include <vector>
#include <algorithm>
#include "../vizinhancas/Vizinhanca.h"
#include "../utils/Util.h"

class VND
{
public:
    void run(std::vector<std::vector<Vizinhanca::Produto>> &melhorSolucao, std::vector<int> &Melhorlinhas, std::vector<std::vector<Vizinhanca::Produto>> &solucao, std::vector<int> &linhas, int numLinhasProducao, int *matrizProd, int numProdutos);

private:
};

#endif // VND_H
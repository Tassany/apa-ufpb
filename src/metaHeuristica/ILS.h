
#ifndef ILS_H
#define ILS_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class ILS
{
private:
public:
    std::vector<int> buscaLocal(std::vector<std::vector<Vizinhanca::Produto>> &solucao);
};

#endif

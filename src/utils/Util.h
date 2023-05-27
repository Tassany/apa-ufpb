#ifndef Util_H
#define Util_H
#include <random>

class Util
{
private:
    
public:
   int gerarNumeroAleatorio(int min, int max);
   int indiceMenorValor(std::vector<int> &vetor, int tamanho);
   int indiceMaiorValor(std::vector<int> &vetor, int tamanho);
};

#endif


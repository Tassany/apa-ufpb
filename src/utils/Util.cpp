#include "Util.h"



int Util::gerarNumeroAleatorio(int min, int max)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}
int Util::indiceMenorValor(std::vector<int> &vetor, int tamanho)
{
    int menor = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] < vetor[menor])
        {
            menor = i;
        }
    }
    return menor;
}
int Util::indiceMaiorValor(std::vector<int> &vetor, int tamanho)
{
    int maior = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] > vetor[maior])
        {
            maior = i;
        }
    }
    return maior;
}
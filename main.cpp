#include <iostream>
#include <fstream>
#include <string>

void quicksort(int *array, int esq, int dir)
{
    int i = esq, j = dir;
    int pivo = array[(esq + dir) / 2];

    while (i <= j)
    {
        // encontrar o primeiro elemento maior que o pivo
        while (array[i] < pivo)
            i++;

        // encontrar o primeiro elemento menor que o pivo
        while (array[j] > pivo)
            j--;

        // swap dos elementos encontrados acima
        if (i <= j)
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    };

    // recursao para as duas metades do array
    if (esq < j)
        quicksort(array, esq, j);
    if (i < dir)
        quicksort(array, i, dir);
}

int main()
{
    std::string fileName = "arquivo.txt"; // Nome do arquivo a ser lido

    // Abre o arquivo
    std::ifstream inputFile(fileName);

    if (!inputFile)
    {
        std::cerr << "Erro ao abrir o arquivo " << fileName << std::endl;
        return 1;
    }

    // Lê e imprime o conteúdo do arquivo linha por linha
    // std::string line;
    // while (std::getline(inputFile, line))
    // {
    //     std::cout << line << std::endl;
    // }

    int numLinhasProducao, numProdutos;

    inputFile >> numLinhasProducao >> numProdutos;

    // ler um array do tamanho do numero de produtos
    int *produtos = new int[numProdutos];

    for (int i = 0; i < numProdutos; i++)
    {
        inputFile >> produtos[i];
    }

    // ler uma matriz de tamanho numProdutos x numProdutos
    int **matriz = new int *[numProdutos];
    for (int i = 0; i < numProdutos; i++)
    {
        matriz[i] = new int[numProdutos];
    }

    // Fecha o arquivo
    inputFile.close();

    std::cout << "Numero de linhas de producao: " << numLinhasProducao << std::endl;
    std::cout << "Numero de produtos: " << numProdutos << std::endl;

    // ordenar o array de produtos
    quicksort(produtos, 0, numProdutos - 1);

    std::cout << "Array ordenado: ";
    for (int i = 0; i < numProdutos; i++)
    {
        std::cout << produtos[i] << " ";
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>

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
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    // Fecha o arquivo
    inputFile.close();

    return 0;
}

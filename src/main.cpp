#include "minMax.hpp"

int main() {
    
   // Abrir o arquivo CSV para escrita
    std::ofstream file("./datasets/resultados.csv");

    if (file.is_open()) {
        // Chamar a função execucao() para escrever os resultados no arquivo CSV
        execucao(file);

        // Fechar o arquivo CSV
        file.close();
        std::cout << "Resultados salvos em resultados.csv" << std::endl;

        executarScriptGnuplot();
    } else {
        std::cout << "Erro ao abrir o arquivo resultados.csv para escrita." << std::endl;
    }

    return 0;
}
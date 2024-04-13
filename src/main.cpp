#include "minMax.hpp"

int main() {
        execucao("./datasets/resultados.csv");
        resultadosMedias("./datasets/resultados.csv", "./datasets/resultadosMedias.csv");
        reorganizacaoArquivoResultados("./datasets/resultados.csv", "./datasets/resultadosMinMax.csv");
        resultadosMedias("./datasets/resultadosMinMax.csv", "./datasets/resultadosMinMaxMedias.csv");
        executarScriptGnuplot(); 
    return 0;
}
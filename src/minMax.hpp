#ifndef MINMAX_HPP
#define MINMAX_HPP

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <stdexcept>
#include <iomanip>
#include <algorithm>

void MaxMin1(int A[], int n, int &Max, int &Min);
void MaxMin2(int A[], int n, int &Max, int &Min);
void MaxMin3(int A[], int n, int &Max, int &Min);
int* gerarVetor(int n);
void execucao(std::string arquivoSaida);
void resultadosMedias(std::string arquivoEntrada, std::string arquivoSaida);
void reorganizacaoArquivoResultados(std::string arquivoEntrada, std::string arquivoSaida); 
void executarScriptGnuplot();

#endif 
#ifndef MINMAX_HPP
#define MINMAX_HPP

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <string>

void MaxMin1(int A[], int n, int &Max, int &Min);
void MaxMin2(int A[], int n, int &Max, int &Min);
void MaxMin3(int A[], int n, int &Max, int &Min);
void imprimirVetor(int* A, int n);
int* gerarVetor(int n);
int compare(const void * a, const void * b);
void execucao(std::ofstream& file);
void executarScriptGnuplot();

#endif // MINMAX_HPP
#include "minMax.hpp"

int* gerarVetor(int n) {
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1001;
    };
    
    return A;
}

void imprimirVetor (int* A, int n) {
    for(int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
}

void MaxMin1(int A[], int n, int &Max, int &Min) {
    Max = A[1];
    Min = A[1];
    for (int i = 1; i < n; ++i) {
        if (A[i] > Max) {
            Max = A[i];
        }
        if (A[i] < Min) {
            Min = A[i];
        }
    }
}

void MaxMin2(int A[], int n, int &Max, int &Min) {
    Max = A[1];
    Min = A[1];
    for (int i = 1; i < n; i++) {
        if (A[i] > Max) {
            Max = A[i];
        } else if (A[i] < Min) {
            Min = A[i];
        }
    }
}

void MaxMin3(int A[], int n, int &Max, int &Min) {
    int i, FimDoAnel;

    if (n % 2 > 0) {
        A[n + 1] = A[n];
        FimDoAnel = n;
    } else {
        FimDoAnel = n - 1;
    }

    if (A[1] > A[2]) {
        Max = A[1];
        Min = A[2];
    } else {
        Max = A[2];
        Min = A[1];
    }

    i = 3;
    while (i <= FimDoAnel) {
        if (A[i] > A[i + 1]) {
            if (A[i] > Max) {
                Max = A[i];
            }
            if (A[i + 1] < Min) {
                Min = A[i + 1];
            }
            if (A[i + 1] > Max) {
                Max = A[i + 1];
            }
            if (A[i] < Min) {
                Min = A[i];
            }
        }
        i = i + 2;
    }
}

int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}
void execucao(std::ofstream& file) {
    int n;
    int Max, Min;
    double tempoExecMedio;
    std::string ordem;
    std::string algoritmo; 

    for (int i = 0; i < 4; i++) { // são as quatro entradas diferentes
        if(i == 0) {
            n = 1000;
        } else if(i == 1) {
            n = 10000;
        } else if(i == 2) {
            n = 100000;
        } else if(i == 3) {
            n = 500000;
        }
        
        int* A = new int[n]; // Aloca um novo vetor com o tamanho determinado
        for (int j = 0; j < 3; j++) { // são os três tipos de organização do vetor
            // Preencher e ordenar o vetor conforme necessário
            if(j == 1) {
                for (int k = 0; k < n; k++) {
                    A[k] = k;
                }
                std::qsort(A, n, sizeof(int), compare);
            } else if(j == 2) {
                for (int k = 0; k < n; k++) {
                    A[k] = n - k;
                }
                std::qsort(A, n, sizeof(int), compare);
            }
            
            for (int k = 0; k < 3; k++) { // são os três tipos de algoritmos
                for (int l = 0; l < 10; l++) { // são as 10 execuções de cada um
                    auto inicio = std::chrono::high_resolution_clock::now();
                    if(k == 0) {
                        MaxMin1(A, n, Max, Min);
                    } else if(k == 1) {
                        MaxMin2(A, n, Max, Min);
                    } else if(k == 2) {
                        MaxMin3(A, n, Max, Min);
                    }              
                    auto fim = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> tempoExec = (fim - inicio);

                    tempoExecMedio += tempoExec.count();
                    if(j == 0) {
                        ordem = "Aleatorio";
                    } else if(j == 1) {
                        ordem = "Crescente";
                    } else if(j == 2) {
                        ordem = "Decrescente";
                    }
                }
                
                tempoExecMedio = tempoExecMedio / 10;
                file << n << "," << ordem << "," << k+1 << "," << tempoExecMedio << "\n";
                tempoExecMedio = 0;
            }
        }
        delete[] A; // Libera a memória alocada para A dentro do loop
    }
}


void executarScriptGnuplot() {
    // Comando para executar o script do Gnuplot
    std::string comando = "cd src && gnuplot plot_script.gp";
    
    // Executando o comando
    int status = system(comando.c_str());
    
    // Verificando se a execução foi bem-sucedida
    if (status != 0) {
        std::cerr << "Erro ao executar o script do Gnuplot." << std::endl;
    } else {
        std::cout << "Script do Gnuplot executado com sucesso." << std::endl;
    }
}

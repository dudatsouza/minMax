#include "minMax.hpp"

void MaxMin1(int A[], int n, int &Max, int &Min) {
    Max = A[0];
    Min = A[0];

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
    Max = A[0];
    Min = A[0];

    for (int i = 1; i < n; i++) {
        if (A[i] > Max) {
            Max = A[i];
        } else if (A[i] < Min) {
            Min = A[i];
        }
    }
}

void MaxMin3(int A[], int n, int &Max, int &Min) {
    int i, FimDoAnel = 0;

    if (n % 2 > 0) {
        A[n] = A[n - 1];
        FimDoAnel = n;
    } else {
        FimDoAnel = n - 1;
    }

    if (A[0] > A[1]) {
        Max = A[0];
        Min = A[1];
    } else {
        Max = A[1];
        Min = A[0];
    }

    i = 2;
    while (i < FimDoAnel) {
        if (A[i] > A[i + 1]) {
            if (A[i] > Max) {
                Max = A[i];
            }
            if (A[i + 1] < Min) {
                Min = A[i + 1];
            }
        } else {
            if (A[i + 1] > Max) {
                Max = A[i + 1];
            }
            if (A[i] < Min) {
                Min = A[i];
            }
        }
        
        i += 2;
    }
}

int* gerarVetor(int n) {
    int* A = new int[n];

    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1001;
    };
    
    return A;
}

void execucao(std::string arquivoSaida) {
    int n;
    int Max, Min;
    double tempoExecMedio;
    std::string ordem;
    std::string algoritmo; 
    std::ofstream outputFile(arquivoSaida);

    if(!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << arquivoSaida << std::endl;
        return;
    }

    std::cout << "Executando algoritmos..." << std::endl;
    for (int i = 0; i < 4; i++) {
        if(i == 0) {
            n = 1000;
        } else if(i == 1) {
            n = 10000;
        } else if(i == 2) {
            n = 100000;
        } else if(i == 3) {
            n = 500000;
        }
        
        int* A = gerarVetor(n);
        for (int j = 0; j < 3; j++) { 
            if(j == 1) {
                std::sort(A, A + n);
            } else if(j == 2) {
                std::sort(A, A + n, std::greater<int>());
            }
            
            for (int k = 0; k < 3; k++) { 
                std::cout << "\n--------------------" << std::endl;
                std::cout << "Tamanho do vetor: " << n << std::endl;
                std::cout << "Ordem: " << ordem << std::endl;
                std::cout << "Algoritmo: MinMax" << k+1 << std::endl << std::endl;
                for (int l = 0; l < 10; l++) {
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
                    if (j == 0) {
                        ordem = "Aleatorio";
                    } else if (j == 1) {
                        ordem = "Crescente";
                    } else if (j == 2) {
                        ordem = "Decrescente";
                    }

                outputFile << n << "," << ordem << "," << k+1 << "," << tempoExec.count() << "\n";
                std::cout << "Execução " << l+1 << std::endl;
                std::cout << "Tempo de execução: " << tempoExec.count() << " ms" << std::endl;
                std::cout << "Max: " << Max << std::endl;
                std::cout << "Min: " << Min << std::endl;
                std::cout << std::endl;
                }
            }
        }
        delete[] A;
    }

    
    std::cout << "Execução finalizada." << std::endl;
    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Resultados salvos em " << arquivoSaida << std::endl;
}

void resultadosMedias (std::string arquivoEntrada, std::string arquivoSaida) {
    std::ifstream inputFile(arquivoEntrada);
    std::ofstream outputFile(arquivoSaida);

    if (!inputFile || !outputFile) {
        std::cerr << "Erro ao abrir os arquivos." << std::endl;
        return;
    }

    std::string line;
    int count = 0;
    double sum = 0.0;
    std::string currentKey;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string key;

        std::getline(ss, token, ',');
        key += token + ",";
        std::getline(ss, token, ',');
        key += token + ",";
        std::getline(ss, token, ',');
        key += token;

        if (std::getline(ss, token, ',')) {
            try {
                double value = std::stod(token);
                sum += value;
                count++;
                currentKey = key;  
            } catch (const std::invalid_argument& e) {
                std::cerr << "Erro ao converter '" << token << "' para double." << std::endl;
                return;
            }
        }

        if (count == 10 && currentKey == key) {
            double average = sum / 10.0;
            outputFile << currentKey << "," << std::fixed << std::setprecision(7) << average << std::endl;

            count = 0;
            sum = 0.0;
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "Media calculada e salva em " << arquivoSaida << std::endl;
}

void reorganizacaoArquivoResultados(std::string arquivoEntrada, std::string arquivoSaida) {
    std::ifstream inputFile(arquivoEntrada);    
    std::string MinMax11, MinMax21, MinMax31;
    std::string MinMax12, MinMax22, MinMax32;
    std::string MinMax13, MinMax23, MinMax33;

    if (!inputFile) {
        std::cerr << "Erro ao abrir arquivo de entrada." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        int ordem;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        int numeroColuna3 = std::stoi(tokens[2]);
        std::string coluna2 = tokens[1];
        if (numeroColuna3 == 1 && coluna2 == "Aleatorio") {
           MinMax11 += line + "\n";
        } else if (numeroColuna3 == 2 && coluna2 == "Aleatorio") {
            MinMax12 += line + "\n";
        } else if (numeroColuna3 == 3 && coluna2 == "Aleatorio") {
            MinMax13 += line + "\n";
        } else if (numeroColuna3 == 1 && coluna2 == "Crescente") {
            MinMax21 += line + "\n";
        } else if (numeroColuna3 == 2 && coluna2 == "Crescente") {
            MinMax22 += line + "\n";
        } else if (numeroColuna3 == 3 && coluna2 == "Crescente") {
            MinMax23 += line + "\n";
        } else if (numeroColuna3 == 1 && coluna2 == "Decrescente") {
            MinMax31 += line + "\n";
        } else if (numeroColuna3 == 2 && coluna2 == "Decrescente") {
            MinMax32 += line + "\n";
        } else if (numeroColuna3 == 3 && coluna2 == "Decrescente") {
            MinMax33 += line + "\n";
        }
    }

    inputFile.close();

    std::ofstream outputFile(arquivoSaida);
    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída." << std::endl;
        return;
    }

    outputFile <<  MinMax11 <<  MinMax21 <<  MinMax31 <<  MinMax12 <<  MinMax22 <<  MinMax32 <<  MinMax13 <<  MinMax23 <<  MinMax33;

    outputFile.close();
    std::cout << "Reorganizacao dos dados para outra analise salva em " << arquivoSaida << std::endl;
}

void executarScriptGnuplot() {
    std::string comando = "cd src && gnuplot plotGraficoMedias.gp && gnuplot plotGraficoMinMax.gp";
    
    int status = system(comando.c_str());
    
    if (status != 0) {
        std::cerr << "Erro ao executar os scripts do Gnuplot." << std::endl;
    } else {
        std::cout << "Scripts do Gnuplot executado com sucesso." << std::endl;
    }
}

set terminal png

# Número de linhas a serem plotadas em cada gráfico
linhas_por_grafico = 4

# Número total de linhas no arquivo
total_linhas = system('wc -l < "../datasets/resultadosMinMaxMedias.csv"')

# Define a função para plotar os dados de acordo com os parâmetros passados
plotarDados(linha_inicial, linha_final, indice, algoritmo, tipo) = sprintf("set terminal png size 900,400\nset output '../images/plots/%s/graficoMinMax%s.png'\nset datafile separator \",\"\nset title \"Grafico MinMax%s, organizado de forma %s\"\nset xlabel \" \"\nset ylabel \"Tempo de Execução\"\nset key font \"Arial, 1\"\nplot \"../datasets/resultadosMinMaxMedias.csv\" every ::%d::%d using 1:4 with lines title \"Tempo de Execução - Linhas\", '' every ::%d::%d using 1:4 with points title \"Tempo de Execução - Pontos\"", tipo, algoritmo, algoritmo, tipo, linha_inicial, linha_final, linha_inicial, linha_final)

# Gera um script para cada conjunto de linhas
do for [linha = 0:total_linhas-linhas_por_grafico:linhas_por_grafico] {
    linha_dados = linha + 1  # A linha dos dados na planilha começa do 1, não do 0
    algoritmo = system(sprintf("awk -F',' 'NR==%d{print $3}' ../datasets/resultadosMinMaxMedias.csv", linha_dados))
    tipo = system(sprintf("awk -F',' 'NR==%d{print $2}' ../datasets/resultadosMinMaxMedias.csv", linha_dados))
    
    linha_inicial = linha
    linha_final = (linha -1) + linhas_por_grafico
    indice = linha / linhas_por_grafico + 1
    script_nome = sprintf("script_%d.gp", indice)
    script = plotarDados(linha_inicial, linha_final, indice, algoritmo, tipo)
    set print script_nome
    print script
    set print
    # Executa o script gerado
    system(sprintf("gnuplot %s", script_nome))
}

# Apaga os scripts gerados após a execução
system("rm script_*.gp")
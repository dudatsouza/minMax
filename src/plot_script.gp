set terminal png

# Número de linhas a serem plotadas em cada gráfico
linhas_por_grafico = 3

# Número total de linhas no arquivo
total_linhas = system('wc -l < "../datasets/resultados.csv"')

# Define a função para plotar os dados de acordo com os parâmetros passados
plotar_dados(linha_inicial, linha_final, indice, n, tipo) = sprintf("set terminal png\nset output '../plots/grafico_%d.png'\nset datafile separator \",\"\nset title \"Gráfico %d - Tempo de Execução\"\nset xlabel \" \"\nset ylabel \"Tempo de Execução\"\nset xtics (\"MinMax1\" 1, \"MinMax2\" 2, \"MinMax3\" 3)\nset label 1 \"Grafico com dados de um vetor de %s posições, organizado de forma %s\" at graph -0.132, -0.095 \nset key font \"Arial, 1\"\nplot \"../datasets/resultados.csv\" every ::%d::%d using 3:4 with lines title \"Tempo de Execução\"", indice, indice, n, tipo, linha_inicial, linha_final)

# Gera um script para cada conjunto de linhas
do for [linha = 0:total_linhas-linhas_por_grafico:linhas_por_grafico] {
    linha_dados = linha + 1  # A linha dos dados na planilha começa do 1, não do 0
    n = system(sprintf("awk -F',' 'NR==%d{print $1}' ../datasets/resultados.csv", linha_dados))
    tipo = system(sprintf("awk -F',' 'NR==%d{print $2}' ../datasets/resultados.csv", linha_dados))
    
    linha_inicial = linha
    linha_final = (linha -1) + linhas_por_grafico
    indice = linha / linhas_por_grafico + 1
    script_nome = sprintf("script_%d.gp", indice)
    script = plotar_dados(linha_inicial, linha_final, indice, n, tipo)
    set print script_nome
    print script
    set print
    # Executa o script gerado
    system(sprintf("gnuplot %s", script_nome))
}

# Apaga os scripts gerados após a execução
system("rm script_*.gp")
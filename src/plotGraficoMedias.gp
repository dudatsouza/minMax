set terminal png

# Número de linhas a serem plotadas em cada gráfico
linhas_por_grafico = 3

# Número total de linhas no arquivo
total_linhas = system('wc -l < "../datasets/resultadosMedias.csv"')

# Define a função para plotar os dados de acordo com os parâmetros passados
plotarDados(linha_inicial, linha_final, indice, n, tipo) = sprintf("set terminal png\nset output '../images/plots/%s/graficoMedia%s.png'\nset datafile separator \",\"\nset title \"Grafico vetor de %s posições, organizado de forma %s\"\nset xlabel \" \"\nset ylabel \"Tempo de Execução\"\nset xtics (\"MinMax1\" 1, \"MinMax2\" 2, \"MinMax3\" 3)\nset key font \"Arial, 1\"\nplot \"../datasets/resultadosMedias.csv\" every ::%d::%d using 3:4 with lines title \"Tempo de Execução - Linhas\", '' every ::%d::%d using 3:4 with points title \"Tempo de Execução - Pontos\"", tipo, n, n, tipo, linha_inicial, linha_final, linha_inicial, linha_final)

# Gera um script para cada conjunto de linhas
do for [linha = 0:total_linhas-linhas_por_grafico:linhas_por_grafico] {
    linha_dados = linha + 1  # A linha dos dados na planilha começa do 1, não do 0
    n = system(sprintf("awk -F',' 'NR==%d{print $1}' ../datasets/resultadosMedias.csv", linha_dados))
    tipo = system(sprintf("awk -F',' 'NR==%d{print $2}' ../datasets/resultadosMedias.csv", linha_dados))
    
    linha_inicial = linha
    linha_final = (linha -1) + linhas_por_grafico
    indice = linha / linhas_por_grafico + 1
    script_nome = sprintf("script_%d.gp", indice)
    script = plotarDados(linha_inicial, linha_final, indice, n, tipo)
    set print script_nome
    print script
    set print
    # Executa o script gerado
    system(sprintf("gnuplot %s", script_nome))
}


# Apaga os scripts gerados após a execução
system("rm script_*.gp") 


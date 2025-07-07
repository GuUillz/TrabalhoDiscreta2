import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

script_dir = Path(__file__).parent.resolve()

# Constrói o caminho para a pasta Resultados
base_path = script_dir
def plotar_grafico(x,y, titulo,label, xlabel, ylabel, color):
    plt.plot(x, y, label=label, color=color)
    plt.title(titulo)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid()
    plt.show()

SIR = base_path /'Resultados/resultados_SIR.csv'  
data = pd.read_csv(SIR)

passo = data['Passo']
sucetivel = data['Sucetivel']
removido = data['Removido']
infectado = data['Infectado']




plotar_grafico(passo, sucetivel, 'Gráfico de pessoas sucetivel ao longo do tempo (SIR)', 'Sucetível', 'Eixo t (dias)', 'Eixo S (número de Pessoas Sucetíveis)', 'orange')
plotar_grafico(passo, removido, 'Gráfico de pessoas removida do estudo ao longo do tempo (SIR)', 'Removido', 'Eixo t (dias)', 'Eixo R (número de Pessoas Removidas)', 'red')
plotar_grafico(passo, infectado, 'Gráfico de infectados ao longo do tempo (SIR)', 'Infectado', 'Eixo t (dias)', 'Eixo I (número de infectados)', 'blue')

SIS = base_path / 'Resultados/resultados_SIS.csv'
data = pd.read_csv(SIS)
passo = data['Passo']
sucetivel = data['Sucetivel']
infectado = data['Infectado']
plotar_grafico(passo, sucetivel, 'Gráfico de pessoas sucetivel ao longo do tempo (SIS)', 'Sucetível', 'Eixo t (dias)', 'Eixo S (número de Pessoas Sucetíveis)', 'orange')
plotar_grafico(passo, infectado, 'Gráfico de infectados ao longo do tempo (SIS)', 'Infectado', 'Eixo t (dias)', 'Eixo I (número de infectados)', 'blue')

SEIR = base_path / 'Resultados/resultados_SEIR.csv'
data = pd.read_csv(SEIR)
passo = data['Passo']
sucetivel = data['Sucetivel']
exposto = data['Exposto']
removido = data['Removido']
infectado = data['Infectado']
plotar_grafico(passo, sucetivel, 'Gráfico de pessoas sucetivel ao longo do tempo (SEIR)', 'Sucetível', 'Eixo t (dias)', 'Eixo S (número de Pessoas Sucetíveis)', 'orange')
plotar_grafico(passo, exposto, 'Gráfico de pessoas expostas ao longo do tempo (SEIR)', 'Exposto', 'Eixo t (dias)', 'Eixo E (número de Pessoas Expostas)', 'purple')
plotar_grafico(passo, removido, 'Gráfico de pessoas removida do estudo ao longo do tempo (SEIR)', 'Removido', 'Eixo t (dias)', 'Eixo R (número de Pessoas Removidas)', 'red')
plotar_grafico(passo, infectado, 'Gráfico de infectados ao longo do tempo (SEIR)', 'Infectado', 'Eixo t (dias)', 'Eixo I (número de infectados)', 'blue')


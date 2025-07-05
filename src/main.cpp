#include "WattsStrogratzGenerator.h"
#include "Simulation.h"

int main()
{

    int N_nós = 1000;
    int N_vizinhos = 4;
    double probabilidade_de_religação = 0.1;
    unsigned int seed_cidade = 42;
    unsigned int seed_sim = 123;
    WattsStrogatzGenerator generator(seed_cidade);
    Graph GrafoDaCidade = generator.generate(N_nós, N_vizinhos, probabilidade_de_religação);
    std::cout << "Grafo gerado com " << GrafoDaCidade.size() << " nós e grau médio de " << N_vizinhos << ".\n";
    std::cout << "Imprimindo o grafo:\n";
    GrafoDaCidade.printGraph();
    SimulacaoParametros params;
    params.beta = 0.3; // Taxa de transmissão
    params.gamma = 0.1; // Taxa de recuperação
    params.epsilon = 0.05; // Taxa de exposição
    params.max_steps = 1000; // Número máximo de passos
    params.num_infectados = 10; // Número inicial de infectados 
    Simulation simulacao1(GrafoDaCidade, params, seed_sim);
    simulacao1.runSIS();
    simulacao1.saveResults("resultados_SIS.csv");
    std::cout<< "Simulação SIS concluída e resultados salvos em 'resultados_SIS.csv'.\n";
    Simulation simulacao2(GrafoDaCidade, params, seed_sim);
    simulacao2.runSIR();
    simulacao2.saveResults("resultados_SIR.csv");
    std::cout<< "Simulação SIR concluída e resultados salvos em 'resultados_SIR.csv'.\n";
    Simulation simulacao3(GrafoDaCidade, params, seed_sim);
    simulacao3.runSEIR();
    simulacao3.saveResults("resultados_SEIR.csv");
    std::cout<< "Simulação SEIR concluída e resultados salvos em 'resultados_SEIR.csv'.\n";
    

}
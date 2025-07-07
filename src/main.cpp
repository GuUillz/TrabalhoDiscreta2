#include "WattsStrogratzGenerator.h"
#include "Simulation.h"
#include "Tarjan.h"
#include <set>

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
    std::cout << "Imprimindo o grafo em : grafo_cidade.txt\n";
    GrafoDaCidade.printGraph("grafo_cidade.txt");
    SimulacaoParametros params;
    params.alpha = 0.3; // Taxa de transmissão
    params.beta = 0.1; // Taxa de recuperação
    params.epsilon = 0.05; // Taxa de exposição
    params.max_steps = 365; // Número máximo de Tempo passado (Dias)
    params.num_infectados = 20; // Número inicial de infectados 

    Simulation simulacao1(GrafoDaCidade, params, seed_sim);
    simulacao1.runSIS();
    simulacao1.saveResults("resultados_SIS.csv");
    std::cout<< "Simulação SIS concluída e resultados salvos em 'resultados_SIS.csv'.\n";
    std::vector<State> pico = simulacao1.getPeakInfectionState();
    std::mt19937 rng(seed_sim);
    DirectedGraph transmission_network = simulacao1.createTransitionGraph(pico, GrafoDaCidade, params.alpha, rng);

    Tarjan cfc_analyzer(transmission_network);
    cfc_analyzer.run();
    const std::vector<int>& node_to_cfc_map = cfc_analyzer.getNodeToCfcMap();

    const std::map<int, std::vector<int>>& cfc_members = cfc_analyzer.getCfcMembers();
    cfc_analyzer.print_cfc_members(cfc_members, "cfc_members_SIS.txt");

    Simulation simulacao2(GrafoDaCidade, params, seed_sim);
    simulacao2.runSIR();
    simulacao2.saveResults("resultados_SIR.csv");
    std::cout<< "Simulação SIR concluída e resultados salvos em 'resultados_SIR.csv'.\n";
    pico = simulacao2.getPeakInfectionState();
    transmission_network = simulacao2.createTransitionGraph(pico, GrafoDaCidade, params.alpha, rng);
    Tarjan cfc_analyzer2(transmission_network);
    cfc_analyzer2.run();
    const std::vector<int>& node_to_cfc_map2 = cfc_analyzer2.getNodeToCfcMap();
    const std::map<int, std::vector<int>>& cfc_members2 = cfc_analyzer2.getCfcMembers();
    cfc_analyzer2.print_cfc_members(cfc_members2, "cfc_members_SIR.txt");



    Simulation simulacao3(GrafoDaCidade, params, seed_sim);
    simulacao3.runSEIR();
    simulacao3.saveResults("resultados_SEIR.csv");
    std::cout<< "Simulação SEIR concluída e resultados salvos em 'resultados_SEIR.csv'.\n";
    pico = simulacao3.getPeakInfectionState();
    transmission_network = simulacao3.createTransitionGraph(pico, GrafoDaCidade, params.alpha, rng);


    Tarjan cfc_analyzer3(transmission_network);
    cfc_analyzer3.run();
    const std::vector<int>& node_to_cfc_map3 = cfc_analyzer3.getNodeToCfcMap();
    const std::map<int, std::vector<int>>& cfc_members3 = cfc_analyzer3.getCfcMembers();
    cfc_analyzer3.print_cfc_members(cfc_members3, "cfc_members_SEIR.txt");



}

#include "WattsStrogratzGenerator.h"
#include "Simulation.h"
#include "Tarjan.h"
#include <set>
using CondensationGraph = std::map<int, std::set<int>>;
CondensationGraph build_condensation_graph(const DirectedGraph& transmission_graph, const std::vector<int>& node_to_scc_map, int scc_count) {
    CondensationGraph condensation_graph;

    for (int i = 1; i <= scc_count; ++i) {
        condensation_graph[i] = std::set<int>();
    }


    for (int u = 0; u < transmission_graph.size(); ++u) {
        int scc_u = node_to_scc_map[u];
        if (scc_u == -1) continue; 

        for (int v : transmission_graph[u]) {
            int scc_v = node_to_scc_map[v];
            if (scc_v == -1) continue;


            if (scc_u!= scc_v) {
                condensation_graph[scc_u].insert(scc_v);
            }
        }
    }
    return condensation_graph;
}

void print_condensation_graph(const CondensationGraph& condensation_graph, const std::string& filename) {
    std::cout << "\n--- Grafo de Condensação (Conexões entre CFCs) ---" << std::endl;
    std::ofstream file(filename);
    for (const auto& pair : condensation_graph) {
        int source_scc_id = pair.first;
        const std::set<int>& target_sccs = pair.second;

        file << "Node_" << source_scc_id << " -> (";
        
        if (target_sccs.empty()) {
            file << ")" << std::endl;
            continue;
        }

        auto it = target_sccs.begin();
        while (it!= target_sccs.end()) {
            file << "Node_" << *it;
            ++it;
            if (it!= target_sccs.end()) {
                file<< ", ";
            }
        }
        file << ")" << std::endl;
    }
    file.close();
    std::cout << "Grafo de condensação salvo em " << filename << std::endl;
}

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
    params.beta = 0.3; // Taxa de transmissão
    params.gamma = 0.1; // Taxa de recuperação
    params.epsilon = 0.05; // Taxa de exposição
    params.max_steps = 1000; // Número máximo de Tempo passado (Dias)
    params.num_infectados = 10; // Número inicial de infectados 

    Simulation simulacao1(GrafoDaCidade, params, seed_sim);
    simulacao1.runSIS();
    simulacao1.saveResults("resultados_SIS.csv");
    std::cout<< "Simulação SIS concluída e resultados salvos em 'resultados_SIS.csv'.\n";
    std::vector<State> pico = simulacao1.getPeakInfectionState();
    std::mt19937 rng(seed_sim);
    DirectedGraph transmission_network = simulacao1.createTransitionGraph(pico, GrafoDaCidade, params.beta, rng);

    Tarjan cfc_analyzer(transmission_network);
    cfc_analyzer.run();
    const std::vector<int>& node_to_cfc_map = cfc_analyzer.getNodeToCfcMap();
    int cfc_count = cfc_analyzer.getCfcCount();

    CondensationGraph condensation_graph = build_condensation_graph(transmission_network, node_to_cfc_map, cfc_count);
    print_condensation_graph(condensation_graph, "condensation_graph_SIS.txt");
   

    Simulation simulacao2(GrafoDaCidade, params, seed_sim);
    simulacao2.runSIR();
    simulacao2.saveResults("resultados_SIR.csv");
    std::cout<< "Simulação SIR concluída e resultados salvos em 'resultados_SIR.csv'.\n";
    pico = simulacao2.getPeakInfectionState();
    transmission_network = simulacao2.createTransitionGraph(pico, GrafoDaCidade, params.beta, rng);
    Tarjan cfc_analyzer2(transmission_network);
    cfc_analyzer2.run();
    const std::vector<int>& node_to_cfc_map2 = cfc_analyzer2.getNodeToCfcMap();
    int cfc_count2 = cfc_analyzer2.getCfcCount();
    CondensationGraph condensation_graph2 = build_condensation_graph(transmission_network, node_to_cfc_map2, cfc_count2);
    print_condensation_graph(condensation_graph2,"condensation_graph_SIR.txt");


    Simulation simulacao3(GrafoDaCidade, params, seed_sim);
    simulacao3.runSEIR();
    simulacao3.saveResults("resultados_SEIR.csv");
    std::cout<< "Simulação SEIR concluída e resultados salvos em 'resultados_SEIR.csv'.\n";
    pico = simulacao3.getPeakInfectionState();
    transmission_network = simulacao3.createTransitionGraph(pico, GrafoDaCidade, params.beta, rng);


    Tarjan cfc_analyzer3(transmission_network);
    cfc_analyzer3.run();
    const std::vector<int>& node_to_cfc_map3 = cfc_analyzer3.getNodeToCfcMap();
    int cfc_count3 = cfc_analyzer3.getCfcCount();
    CondensationGraph condensation_graph3 = build_condensation_graph(transmission_network, node_to_cfc_map3, cfc_count3);
    print_condensation_graph(condensation_graph3,"Condensation_graph_SEIR.txt");  
  


}

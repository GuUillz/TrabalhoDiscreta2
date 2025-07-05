#include "Simulation.h"
Simulation::Simulation(const Graph& graph, const SimulacaoParametros& params, const size_t seed)
    : graph(graph), params(params), rng(seed), dist(0.0, 1.0) {

        node_states.resize(graph.size(), State::Sucetivel);
        inicializar();

    }
void Simulation::runSIS()
{
recordStateCounts();
for(int passo = 0; passo < params.max_steps; passo++) {
    if(getInfectedCount() == 0) {
        break; 
    }
    stepSIS();
    recordStateCounts();   

} 
}
void Simulation::runSIR()
{
recordStateCounts();
for(int passo = 0; passo < params.max_steps; passo++) {
    if(getInfectedCount() == 0) {
        break; 
    }
    stepSIR();
    recordStateCounts();   

} 
}
void Simulation::runSEIR()
{
recordStateCounts();
for(int passo = 0; passo < params.max_steps; passo++) {
    if(getInfectedCount() == 0 && getExposedCount() == 0) {
        break; 
    }
    stepSEIR();
    recordStateCounts();        
}
}

void Simulation::saveResults(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Não foi possivel abrir o arquivo: " + filename);
    }
    outfile << "Passo,Sucetivel,Infectado,Exposto,Removido\n";
    for (size_t i = 0; i < resultados.size(); ++i) {
        outfile << i << ","

                << resultados[i].at(State::Sucetivel) << ","
                << resultados[i].at(State::Infectado) << ","
                << resultados[i].at(State::Exposto) << ","
                << resultados[i].at(State::Removido) << std::endl;
    }
    outfile.close();
}

void Simulation::inicializar() {
    std::uniform_int_distribution<> node_dist(0, graph.size() - 1);
    for (int i = 0; i < params.num_infectados; ++i) {
        int node_idx;
        do
        {
            node_idx = node_dist(rng);
        }while(node_states[node_idx] == State::Infectado);
        node_states[node_idx] = State::Infectado;
    }
}

void Simulation::stepSIS() {
    std::vector<State> next_states = node_states;
    int N = graph.size();

    for (int i = 0; i < N; i++) {
        if (node_states[i] == State::Infectado) {
            // Tentativa de transmissão para vizinhos
            for (int neighbor : graph[i]) {
                if (node_states[neighbor] == State::Sucetivel && dist(rng) < params.beta) {
                    next_states[neighbor] = State::Infectado;
                }
            }
            // Tentativa de recuperação para Suscetível
            if (dist(rng) < params.gamma) {
                next_states[i] = State::Sucetivel;
            }
        }
    }
    node_states = next_states;
}

void Simulation::stepSIR() {
    std::vector<State> next_states = node_states;
    int N = graph.size();

    for (int i = 0; i < N; i++) {
        if (node_states[i] == State::Infectado) {
            // Tentativa de transmissão para vizinhos
            for (int neighbor : graph[i]) {
                if (node_states[neighbor] == State::Sucetivel && dist(rng) < params.beta) {
                    next_states[neighbor] = State::Infectado;
                }
            }
            // Tentativa de recuperação
            if (dist(rng) < params.gamma) {
                next_states[i] = State::Removido;
            }
        }
    }
    node_states = next_states;
}


void Simulation::stepSEIR() {
    std::vector<State> next_states = node_states;
    int N = graph.size();

    for (int i = 0; i < N; i++) {
        if (node_states[i] == State::Infectado) {
            // Tentativa de transmissão para vizinhos
            for (int neighbor : graph[i]) {
                if (node_states[neighbor] == State::Sucetivel && dist(rng) < params.beta) {
                    next_states[neighbor] = State::Exposto;
                }
            }
            // Tentativa de recuperação
            if (dist(rng) < params.gamma) {
                next_states[i] = State::Removido;
            }
        } else if (node_states[i] == State::Exposto) {
            // Transição de Exposto para Infectado
            if (dist(rng) < params.epsilon) {
                next_states[i] = State::Infectado;
            }
        }
    }
    node_states = next_states;
}

void Simulation::recordStateCounts() {
    std::map<State, int> state_counts = {
        {State::Sucetivel, 0},
        {State::Infectado, 0},
        {State::Exposto, 0},
        {State::Removido, 0}
    };
    for (const auto& state : node_states) {
        state_counts[state]++;
    }
    resultados.push_back(state_counts);
}
int Simulation::getInfectedCount() const {
    return std::count(node_states.begin(), node_states.end(), State::Infectado);
}
int Simulation::getExposedCount() const {
    return std::count(node_states.begin(), node_states.end(), State::Exposto);
}



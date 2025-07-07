#pragma once
#include "Graph.h"
#include "DirectedGraph.h"
#include <random>
#include <map>
#include <algorithm>
enum class State {
    Sucetivel,
    Infectado,
    Removido,
    Exposto
};
struct SimulacaoParametros
{
double beta;
double alpha;
double epsilon = 0.0; 
int max_steps = 1000;
int num_infectados = 1;

};
class Simulation 
{
public:
Simulation(const Graph& graph, const SimulacaoParametros& params, const size_t seed);
void runSIS();
void runSIR();
void runSEIR();
void saveResults(const std::string& filename) const;
DirectedGraph createTransitionGraph(const std::vector<State>&, const Graph&, const double&, std::mt19937&) const;
const std::vector<State>& getPeakInfectionState() const {
    return VetorEstadosPico;
}
int getPeakInfectionStep() const {
    return pico_infectados;
}
const std::vector<State>& getNodeStates() const {
    return node_states;
}
int getInfectedCount() const;
int getExposedCount() const;

private:
const Graph& graph;
SimulacaoParametros params;
std::vector<State> node_states;
std::vector<std::map<State, int>> resultados;
std::mt19937 rng;
std::uniform_real_distribution<> dist;


void inicializar();
void stepSIS();
void stepSIR();
void stepSEIR();
void recordStateCounts();

int pico_infectados = 0;
int passo_pico = -1;
std::vector<State> VetorEstadosPico;

};
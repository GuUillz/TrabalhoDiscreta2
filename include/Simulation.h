#pragma once
#include "Commons.h"
#include <random>
#include <map>
#include <fstream>
#include <string>
#include "Graph.h"

enum class State {
    Sucetivel,
    Infectado,
    Removido,
    Exposto
};
struct SimulacaoParametros
{
double beta;
double gamma;
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
int getInfectedCount() const;
int getExposedCount() const;


};
#include "WattsStrogratzGenerator.h"

WattsStrogatzGenerator::WattsStrogatzGenerator(const unsigned int& seed) : rng(seed) {}

Graph WattsStrogatzGenerator::generate(const int& numNodes, const int& k, const double& p) {
    if (k >= numNodes || k % 2 != 0 || k < 0) {
        throw std::invalid_argument("k deve ser menor que o numero de nos, nao negativo e par");
    }
    Graph graph = createRing(numNodes, k);
    rewireGraph(graph, k, p);// k = grau de cada no, p = probabilidade de rewire
    return graph;
}
Graph WattsStrogatzGenerator::createRing(const int& numNodes, const int& k) {
    Graph graph(numNodes);
    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % numNodes;
            graph.addEdge(i,neighbor);
        }
    }
    return graph;
}

void WattsStrogatzGenerator::rewireGraph(Graph& graph, const int& k, const double& p) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> node_dist(0, graph.size() - 1);

    for (int i = 0; i < graph.size(); i++) {
        std::vector<int> vizinhos_originais;
        for (int j = 1; j <= k / 2; j++) {
            vizinhos_originais.push_back((i + j) % graph.size());
            }
        for (int neighbor : vizinhos_originais) {
            if(dist(rng)<p)
            {
                graph.erase(neighbor,i);
                int newNeighbor;
                do
                {
                    newNeighbor = node_dist(rng);
                }while (newNeighbor ==i || graph[newNeighbor].count(i) > 0);

                graph.addEdge(i, newNeighbor);
            }
      }
        }
        std::mt19937 rng;
    }

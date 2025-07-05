#include "Graph.h"

Graph::Graph(const int& numNodes) : adjacencyList(numNodes) {}
void Graph::addEdge(const int& u, const int& v) {
    if (u < 0 || u >= adjacencyList.size() || v < 0 || v >= adjacencyList.size()) {
        throw std::out_of_range("Node index out of range");
    }
    adjacencyList[u].insert(v);
    adjacencyList[v].insert(u); 
}
const std::unordered_set<int>& Graph::getNeighbors(const int& node) const {
    if (node < 0 || node >= adjacencyList.size()) {
        throw std::out_of_range("Node index out of range");
    }
    return adjacencyList[node];
}
void Graph::erase(const int u, const int v)
{
    if (u < 0 || u >= adjacencyList.size() || v < 0 || v >= adjacencyList.size()) {
        throw std::out_of_range("Node index out of range");
    }
    adjacencyList[v].erase(u);
    adjacencyList[u].erase(v);

}
void Graph::printGraph() const {
    for (int i = 0; i < adjacencyList.size(); i++) {
        std::cout << "Node " << i << ": ";
        for (const auto& neighbor : adjacencyList[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
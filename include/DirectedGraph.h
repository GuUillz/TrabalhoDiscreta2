#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class DirectedGraph 
{
    public:
    DirectedGraph(const int& numNodes) : outEdges(numNodes) {}
    void addEdge(const int& u, const int& v) {
        if (u < 0 || u >= outEdges.size() || v < 0 || v >= outEdges.size()) {
            throw std::out_of_range("Node index out of range");
        }
        outEdges[u].push_back(v);
    }
    const std::vector<int>& getNeighbors(const int& node) const {
        if (node < 0 || node >= outEdges.size()) {
            throw std::out_of_range("Node index out of range");
        }
        return outEdges[node];
    }
    int size() const {
        return outEdges.size();
    }
    std::vector<int> operator[](const int& u) const {
        if (u < 0 || u >= outEdges.size()) {
            throw std::out_of_range("Node index out of range");
        }
        return outEdges[u];
    }

    void printGraph(const std::string& filename) const {
        std::ofstream file(filename);
        for (int i = 0; i < outEdges.size(); i++) {
            file << "Node " << i << ": ";
            for (const auto& neighbor : outEdges[i]) {
                file << neighbor << " ";
            }
            file << std::endl;
        }
    }


    private:
    std::vector<std::vector<int>> outEdges; // Lista de adjacência
};
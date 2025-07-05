#pragma once
#include "Commons.h"
class Graph {
public:
    Graph(const int&);

    void addEdge(const int&, const int&);
    const std::unordered_set<int>& getNeighbors(const int&) const;
    int size() const {
        return adjacencyList.size();
    };

    const std::unordered_set<int>& operator[](const int& u) const {
        return getNeighbors(u);
    }
    void erase(const int, const int);
    void printGraph() const;
    private:
    std::vector<std::unordered_set<int>> adjacencyList;

};
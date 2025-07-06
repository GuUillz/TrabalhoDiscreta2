#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
class Graph {
public:
    Graph(const int&);

    void addEdge(const int&, const int&);
 
    int size() const {
        return adjacencyList.size();
    };

    const std::unordered_set<int>& operator[](const int& u) const {
        return getNeighbors(u);
    }
    void erase(const int, const int);
    void printGraph(const std::string&) const;
    private:
    std::vector<std::unordered_set<int>> adjacencyList;
    const std::unordered_set<int>& getNeighbors(const int&) const;

};
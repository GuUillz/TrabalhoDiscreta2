#pragma once
#include"Commons.h"
#include "Graph.h"
#include "DirectedGraph.h"
#include <stack>

class Tarjan
{

public:
    Tarjan(const DirectedGraph& graph);
    std::vector<std::vector<int>> findCFCS();
    void find_cfcs_util(int u) {
        disc[u] = low[u] = ++time;
        st.push(u);
        onStack[u] = true;

        for (int v : graph[u]) {
            if(v < 0 || v >= N) {
                throw std::out_of_range("Node index out of range in find_cfcs_util");
            }
            if (disc[v] == -1) {
                find_cfcs_util(v);
                low[u] = std::min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            cfc_count++;
            while (true) {
                int node_in_scc = st.top();
                st.pop();
                onStack[node_in_scc] = false;
                node_to_cfc_map[node_in_scc] = cfc_count; 
                if (u == node_in_scc) break;
            }
        }
    }
    void run() {
        for (int i = 0; i < N; ++i) {
            if (disc[i] == -1 &&!graph[i].empty()) {
                find_cfcs_util(i);
            }
        }
    }
    const std::vector<int>& getNodeToCfcMap() const {
        return node_to_cfc_map;
    }
    int getCfcCount() const {
        return cfc_count;
    }

private:
    const DirectedGraph& graph;
    int N;
    int time;
    std::vector<int> disc; // Tempos de descoberta
    std::vector<int> low;  // Valores de low-link
    std::vector<bool> onStack; // Para verificar se um nó está na pilha de recursão
    std::stack<int> st;
    std::vector<std::vector<int>> cfcs;
    void dfs(int);
    std::vector<int> node_to_cfc_map; 
    int cfc_count;


};
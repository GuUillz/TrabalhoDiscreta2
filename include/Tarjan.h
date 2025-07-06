#pragma once

#include "Graph.h"
#include "DirectedGraph.h"
#include <stack>
#include <map>

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
            std::vector<int> cfc_atual_nodes;
            while (true) {
                int node_in_scc = st.top();
                st.pop();
                onStack[node_in_scc] = false;
                node_to_cfc_map[node_in_scc] = cfc_count; 
                cfc_atual_nodes.push_back(node_in_scc);
                if (u == node_in_scc) break;
            }
            cfcs_members[cfc_count] = cfc_atual_nodes;
            
        }
    }
    const std::map<int, std::vector<int>>& getCfcMembers() const {
        return cfcs_members;
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

    void print_cfc_members(const std::map<int, std::vector<int>>& cfc_members, const std::string& filename) const {
        std::ofstream file(filename);
        std::cout << "\nLista de Membros por Componente Fortemente Conectado" << std::endl;
    
        
        for (const auto& pair : cfc_members) {
            int scc_id = pair.first;
            const std::vector<int>& members = pair.second;
    
            file << "CFC_" << scc_id << " (Tamanho: " << members.size() << ") = (";
    
            for (size_t i = 0; i < members.size(); ++i) {
                file << "Node_" << members[i];
                if (i < members.size() - 1) {
                    file << ", ";
                }
            }
            file << ")" << std::endl;
        }
        file.close();
        std::cout << "Lista de membros por componente fortemente conectado salva em " << filename << std::endl;
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
    std::map<int, std::vector<int>> cfcs_members;
    int cfc_count;


};
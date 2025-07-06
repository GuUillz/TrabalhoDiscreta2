#include "Tarjan.h"

Tarjan::Tarjan(const DirectedGraph& graph) : graph(graph){
    N = graph.size();
    disc.assign(N, -1);
    low.assign(N, -1);
    onStack.assign(N, false);
    node_to_cfc_map.assign(N, -1);
    time = 0;
    cfc_count = 0;

}

std::vector<std::vector<int>> Tarjan::findCFCS() {
    for (int i = 0; i < N; ++i) {
        if (disc[i] == -1) {
            dfs(i);
        }
    }
    return cfcs;
}


void Tarjan::dfs(int u) {
    disc[u] = low[u] = time++;
    st.push(u);
    onStack[u] = true;

    for (int v : graph[u]) {
        if (disc[v] == -1) { 
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        } else if (onStack[v]) { 
            low[u] = std::min(low[u], disc[v]);
        }
    }


    if (low[u] == disc[u]) {
        std::vector<int> current_scc;
        while (true) {
            int node = st.top();
            st.pop();
            onStack[node] = false;
            current_scc.push_back(node);
            if (node == u) break;
        }
        cfcs.push_back(current_scc);
    }
};

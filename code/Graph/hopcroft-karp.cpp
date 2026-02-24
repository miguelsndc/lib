/*
================================================================================
  Hopcroft-Karp - Emparelhamento Máximo Bipartido
  Complexidade: O(E * sqrt(V)) constante melhor q dinic
================================================================================
  1. O grafo deve ser dividido em duas partições: Esquerda (tamanho 'n') e Direita (tamanho 'm').
  2. 1 indexado
  3. Adicione arestas sempre da ESQUERDA para a DIREITA: hk.add_edge(u, v);
  4. Chame hk.max_matching() para obter o tamanho do emparelhamento máximo.
  
================================================================================
*/

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;
    const int INF = 1e9;

    HopcroftKarp(int n, int m) : n(n), m(m), adj(n + 1), matchL(n + 1, 0), matchR(m + 1, 0), dist(n + 1, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!matchL[u]) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[0] = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[matchR[v]] == INF) {
                        dist[matchR[v]] = dist[u] + 1;
                        q.push(matchR[v]);
                    }
                }
            }
        }
        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                if (dist[matchR[v]] == dist[u] + 1) {
                    if (dfs(matchR[v])) {
                        matchR[v] = u;
                        matchL[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (!matchL[u] && dfs(u)) {
                    res++;
                }
            }
        }
        return res;
    }
};
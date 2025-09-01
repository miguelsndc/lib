/*
Bellmand Ford Single Source Shortest Path
    Complexidade O(VE)
    Encontra ciclos negativos
*/

struct Edge {
    int from, to, cost;
    Edge(int _f, int _t, int _c): from(_f), to(_t), cost(_c) {}
};
vector<ll> BellmanFord(int n, vector<Edge> &g, int src) {
    vector<ll> distance(n, INF);
    distance[src] = 0;
    for (int u = 0; u < n - 1; u++) {
        for (auto edge : g) {
            auto [from, to, cost] = edge;
            distance[to] = min(distance[to], distance[from] + cost);
        }
    }

    vector<int> negative_cycle(n);
    for (auto edge : g) {
        auto [from, to, cost] = edge;
        if (distance[from] + cost < distance[to]) {
            distance[to] = -INF;
            negative_cycle[to] = true;
        }
    }

    // propaga ciclo negativo e encontra os nos afetados - O(VE)
    for (int u = 0; u < n; u++) {
        if (negative_cycle[u]) {
            queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (auto [from, to, cost] : g) {
                    if (from == node && !negative_cycle[to]) {
                        negative_cycle[to] = true;
                        q.push(to);
                    }
                }
            }
        }
    }

    // Marca os nos afetados por ciclos negativos
    for (int i = 0; i < n; i++) {
        if (negative_cycle[i]) {
            distance[i] = -INF;
        }
    }

    return distance;
}

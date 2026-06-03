vector<int> g[ms], bridge_tree[ms];
int dfn[ms], low[ms], timer = 0, vis[ms];
set<pair<int,int>> pontes;
void acha_pontes(int u, int p = -1) {
    dfn[u] = low[u] = timer++;
    for (int v : g[u]) {
        if (v == p) continue;
        if (dfn[v] == -1) {
            acha_pontes(v,u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                // (u,v) é uma bridge
                //process(u,v);
                pontes.insert(minmax(u,v));
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void build_tree(int n) {
    int cc = 0;
    // assumindo q o grafo é conexo e nao-ponderado
    acha_pontes(0);
    vector<int> component(n);
    auto dfs = [&] (auto &&self, int u, int num)->void {
        component[u]=num;
        for (int v: g[u]) {
            if (!pontes.count(minmax(u,v)) and !vis[v]) {
                self(self, v, num);
            }
        }
    };
    for (int u=0;u<n;u++) {
        if (!vis[u]) dfs(dfs, u, cc++);
    }
    for (auto &[u,v]:pontes) {
        bridge_tree[component[u]].push_back(component[v]);
        bridge_tree[component[v]].push_back(component[u]);
    }
}

/*
    O(n + m log m) pra construir a bridge tree
    tambem é possivel construir em O(n+m) se guardar o id da aresta
    e setar ponte[aresta]=true pra toda ponte
*/

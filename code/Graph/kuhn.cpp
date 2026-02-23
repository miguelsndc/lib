/*
 * Algoritmo de Kuhn (Maximum Bipartite Matching)
 * Encontra maximum matching bipartido.
 * Complexidade: O(V * E) no pior caso.
 * * Como usar e recuperar a resposta:
 * 1. Instancie: Kuhn k(n, m); // n = tam. lado esquerdo, m = tam. lado direito
 * 2. Adicione arestas (0-indexado): k.add_edge(u, v);
 * 3. Pegue o total de pares: int max_match = k.matching();
 * 4. Recupere quem ficou com quem olhando o vetor 'mt' (dono do lado direito):
 * for(int v = 0; v < m; v++) {
 * if(k.mt[v] != -1) {
 *  // O vertice 'k.mt[v]' (Esquerda) pegou o vertice 'v' (Direita)
 * }
 * }
 */

struct Kuhn {
    int n, m, iter = 0;
    vector<vector<int>> adj;
    vector<int> mt, vis;
    Kuhn(int n, int m) : n(n), m(m), adj(n), mt(m, -1), vis(n, 0) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
    bool dfs(int u) {
        vis[u] = iter;
        for (int v : adj[u]) {
            if (mt[v] == -1 or (vis[mt[v]] != iter and dfs(mt[v]))) {
                mt[v] = u;
                return true;
            }
        }
        return false;
    }
    int matching() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            iter++; if (dfs(i)) ans++;
        }
        return ans;
    }
};
struct LCA {
    using P = pair<int, int>;
    vector<int> in, h; vector<vector<P>> t;
    void dfs(int u, int p, int d, const vector<vector<int>>& g) {
        h[u] = d; in[u] = t[0].size(); t[0].push_back({d, u});
        for (int v : g[u]) if (v != p) dfs(v, u, d + 1, g), t[0].push_back({d, u});
    }
    LCA(const vector<vector<int>>& g) : in(g.size()), h(g.size()), t(1) {
        dfs(0, -1, 0, g);
        int m = t[0].size(), k = __lg(m) + 1; t.resize(k, vector<P>(m));
        for (int i = 1; i < k; i++) for (int j = 0; j + (1 << i) <= m; j++)
            t[i][j] = min(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }
    int query(int u, int v) {
        auto [l, r] = minmax(in[u], in[v]); int p = __lg(r - l + 1);
        return min(t[p][l], t[p][r - (1 << p) + 1]).second;
    }
    int dist(int u, int v) { return h[u] + h[v] - 2 * h[query(u, v)]; }
};

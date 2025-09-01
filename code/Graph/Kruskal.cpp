struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int a, int b, int c): u(a), v(b), w(c) {}
    bool operator<(const Edge &s) const { return w < s.w; }
};

/*
    Encontra o custo da Arvore Geradora Minima
    Complexidade O(E log E)
    find(u) e unite(u, v) de Union-Find
*/

ll Kruskal(vector<Edge> &g) {
    sort(begin(g), end(g));
    ll total = 0;
    for (auto [u, v, w]: g) {
        if (find(u) != find(v)) {
            unite(u, v);
            total += w;
        }
    }
    return total;
}



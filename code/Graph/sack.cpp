void add(int u, int val) {}
void put(int u, int p, int val) {}
void sack(int u, int p, int keep) {
    int big = -1;
    for (int v: g[u]) {
        if (v == p) continue;
        if (big == -1 or sz[v] > sz[big]) {
            big = v;
        }
    }
    for (int v: g[u]) {
        if (v == p or v == big) continue;
        sack(v, u, 0);
    }
    if (big != -1) sack(big, u, 1);
    add(u, 1);
    for (int v : g[u]) {
        if (v == p or v == big) continue;
        put(v, u, 1);
    }   
    ans[u] = ;
    if (!keep) {
        put(u, p, -1);
    }
}
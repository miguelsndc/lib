void preprocess(int n) {
    for (int v = 0; v < n; v++)
        up[v][0] = parent[v];
    for (int i = 1; i < log2dist; i++) {
        for (int v = 0; v < n; v++) {
            if (v != 0) depth[v] = depth[parent[v]] + 1;
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
    }
}

void dfs(int u, int p = 0) {
    for (int v : tree[u]) {
        if (v != p) {
            dfs(v, u);
            parent[v] = u;
        }
    }
}

int kth_ancestor(int node, int k) {
    if (depth[node] < k) return -1;
    for (int i = 0; i < log2dist; i++) {
        if (k & (1 << i)) {
            node = up[node][i];
        }
    }
    return node + 1;
}
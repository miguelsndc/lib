const int maxn = 2e5 + 5;
int n, a[maxn];
vector tree(4 * maxn, vector<int>());
void build(int l = 0, int r = n - 1, int v = 0) {
    if (l == r) {
        tree[v].push_back(a[l]);
    } else {
        int m = (l + r) / 2;
        build(l, m, v * 2 + 1);
        build(m + 1, r, v * 2 + 2);
        tree[v].resize(tree[v * 2 + 1].size() + tree[v * 2 + 2].size());
        merge(tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(),
              tree[v * 2 + 2].begin(), tree[v * 2 + 2].end(),
              tree[v].begin());
    }
}
int query(int a, int b, int l = 0, int r = n - 1, int v = 0) {
    if (b < l or a > r) return {};
    if (a <= l and r <= b) {
        // responde query
    }
    int m = (l + r) / 2;
    int left = query(a, b, l, m, v * 2 + 1);
    int right = query(a, b, m + 1, r, v * 2 + 2);
    return left + right;
}
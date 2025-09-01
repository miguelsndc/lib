/*
    Geralmente queries em O(nlog²n) sem update
*/

int n;
vector<int> tree[4 * maxn], a;
void build(int l = 0, int r = n - 1, int v = 0) {
    if (l == r) {
        tree[v].push_back(a[l]);
    } else {
        int m = (l + r) / 2;
        build(l, m, v * 2 + 1);
        build(m + 1, r, v * 2 + 2);
        int i = 0, j = 0;
        while (i < tree[v * 2 + 1].size() and j < tree[v * 2 + 2].size()) {
            if (tree[v * 2 + 1][i] < tree[v * 2 + 2][j])
                tree[v].push_back(tree[v * 2 + 1][i++]);
            else
                tree[v].push_back(tree[v * 2 + 2][j++]);
        }
        while (i < tree[v * 2 + 1].size())
            tree[v].push_back(tree[v * 2 + 1][i++]);
        while (j < tree[v * 2 + 2].size())
            tree[v].push_back(tree[v * 2 + 2][j++]);
    }
}

int query(int a, int b, int k, int l = 0, int r = n - 1, int v = 0) {
    if (b < l || a > r) return 0;
    if (l >= a and r <= b) {
        // answer query
    }
    int m = (l + r) / 2;
    int half1 = query(a, b, k, l, m, v * 2 + 1);
    int half2 = query(a, b, k, m + 1, r, v * 2 + 2);
    return half1 + half2;
}

int n; vector<int> tree;
int join(int a, int b) {}
void build(vector<int>& a, int l = 0, int r = n - 1, int v = 0) {
    if (l == r) {
        tree[v] = a[l];
        return;
    } else {
        int mid = l + (r - l) / 2;
        build(a, l, mid, v * 2 + 1);
        build(a, mid + 1, r, v * 2 + 2);
        tree[v] = join(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
}

void update(int pos, int val, int l = 0, int r = n - 1, int v = 0) {
    if (l == r) {
        tree[v] = val;
        return;
    } else {
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            update(pos, val, l, mid, v * 2 + 1);
        } else {
            update(pos, val, mid + 1, r, v * 2 + 2);
        }
        tree[v] = join(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
}

int query(int a, int b, int l = 0, int r = n - 1, int v = 0) {
    if (b < l || a > r) return NEUTRAL;
    if (a <= l && r <= b) return tree[v];
    int mid = l + (r - l) / 2;
    int left = query(a, b, l, mid, v * 2 + 1);
    int right = query(a, b, mid + 1, r, v * 2 + 2);
    return join(left, right);
}

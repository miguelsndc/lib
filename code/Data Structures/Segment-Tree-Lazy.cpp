template <typename T>
class LazySegmentTree {
private:
    const int sz;
    vector<T> tree;
    vector<T> lazy;

    void apply(int v, int len, T add) {
        tree[v] += add * len;
        lazy[v] += add;
    }

    void pushdown(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;
    }

    void build(vector<T> &a, int v, int l, int r) {
        if (l == r) {
            tree[v] = a[l];
        } else {
            int m = l + (r - l) / 2;
            build(a, v * 2, l, m);
            build(a, v * 2 + 1, m + 1, r);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    void range_add(int v, int l, int r, int ql, int qr, int add) {
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l and r <= qr) {
            apply(v, r - l + 1, add);
        } else {
            pushdown(v, l, r);
            int m = (l + r) / 2;
            range_add(2 * v, l, m, ql, qr, add);
            range_add(2 * v + 1, m + 1, r, ql, qr, add);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    T range_sum(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l and r <= qr) return tree[v];
        pushdown(v, l, r);
        int m = (l + r) / 2;
        return range_sum(2 * v, l, m, ql, qr) + range_sum(2 * v + 1, m + 1, r, ql, qr);
    }

public:
    LazySegmentTree(int n) : sz(n), lazy(4 * n), tree(4 * n) {}

    void add(int ql, int qr, int add) {
        range_add(1, 0, sz - 1, ql, qr, add);
    }

    T qry(int ql, int qr) {
        return range_sum(1, 0, sz - 1, ql, qr);
    }

    void build_seg(vector<T> &a) {
        build(a, 1, 0, sz - 1);
    }
};

/*
    Range sum Lazy Segment Tree
    Allows for range updates and range queries
    Query - O(log(n))
    Update - O(log(n))
    Apply - O(1)
    Build - O(n)
*/
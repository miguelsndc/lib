enum QueryType { ADD, SET, NONE };
struct Query {
    QueryType type = NONE;
    ll val = 0;
};
template<typename T> class LazySegtree {
private:
    const int n;
    vector<T> tree;
    vector<Query> lazy;
    void pull(int v) {
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }
    void build(const vector<T>& a, int l, int r, int v = 0) {
        if (l == r) {
            tree[v] = a[l];
        }
        else {
            int m = (l + r) / 2;
            build(a, l, m, v * 2 + 1);
            build(a, m + 1, r, v * 2 + 2);
            pull(v);
        }
    }
    void apply(int v, int len, const Query& x) {
        if (x.type == ADD) {
            if (lazy[v].type != SET) {
                lazy[v] = Query{ ADD,lazy[v].val + x.val };
            }
            else {
                lazy[v] = Query{ SET,lazy[v].val + x.val };
            }
            tree[v] += x.val * len;
        }
        else if (x.type == SET) {
            tree[v] = x.val * len;
            lazy[v] = x;
        }
    }
    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(v * 2 + 1, m - l + 1, lazy[v]);
        apply(v * 2 + 2, r - m, lazy[v]);
        lazy[v] = Query();
    }
    void range_update(int ql, int qr, int l, int r, const Query& x, int v) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, x);
        }
        else {
            push_down(v, l, r);
            int m = (l + r) / 2;
            range_update(ql, qr, l, m, x, v * 2 + 1);
            range_update(ql, qr, m + 1, r, x, v * 2 + 2);
            pull(v);
        }
    }

    T range_sum(int ql, int qr, int l, int r, int v) {
        if (qr < l or ql > r) return 0;
        if (l >= ql and r <= qr) return tree[v];
        push_down(v, l, r);
        int m = (l + r) / 2;
        return range_sum(ql, qr, l, m, v * 2 + 1) + range_sum(ql, qr, m + 1, r, v * 2 + 2);
    }
public:
    LazySegtree(const vector<T>& a) : n(a.size()), tree(4 * n), lazy(4 * n) {
        build(a, 0, n - 1);
    }

    void range_update(int ql, int qr, const Query& x) {
        range_update(ql, qr, 0, n - 1, x, 0);
    }

    T range_sum(int ql, int qr) { return range_sum(ql, qr, 0, n - 1, 0); }
};

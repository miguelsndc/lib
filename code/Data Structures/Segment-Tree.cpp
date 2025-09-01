// 1-Based Segment Tree - Range Queries
const int MAXN = 2e5 + 5;

template<typename T>
struct SegmentTree {
    private:
        vector<T> tree;
        const int NEUTRAL = 1e9 + 9;
        const int n;
    public:

    SegmentTree(int _n): n(_n) {
        tree.resize(4 * n);
    }

    int join(int a, int b) {}

    // O(n) a is a 1-based array
    void build(vector<T> &a, int l = 1, int r = n, int v = 1) {
        if (l == r) {
            tree[v] = a[l];
            return;
        } else {
            int mid = l + (r - l) / 2;
            build(a, l, mid, v * 2);
            build(a, mid + 1, r, v * 2 + 1);
            tree[v] = join(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    // O(log(n))
    void update(int pos, int val, int l = 1, int r = n, int v = 1) {
        if (l == r) {
            tree[v] = val;
            return;
        } else {
            int mid = l + (r - l) / 2;
            if (pos <= mid) {
                update(pos, val, l, mid, v * 2);
            } else {
                update(pos, val, mid + 1, r, v * 2 + 1);
            }
            tree[v] = join(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    // O(log(n))
    i64 query(int a, int b, int l = 1, int r = n, int v = 1) {
        if (b < l || a > r) return NEUTRAL;
        if (a <= l && r <= b) return tree[v];
        int mid = l + (r - l) / 2;
        i64 left = query(a, b, l, mid, v * 2);
        i64 right = query(a, b, mid + 1, r, v * 2 + 1);
        return join(left, right);
    }
};

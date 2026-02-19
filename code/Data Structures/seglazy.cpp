struct Tag {
    Tag() {
    }
    Tag(ll x) {
    }
    void compose(const Tag& t) {}
};

struct Node {
    Node() = default;
    Node(ll v) {
    }
    void apply(const Tag& t) {
    }
    static inline Node merge(Node& left, Node& right) {
    }
};

Node seg[4 * ms];
Tag lazy[4 * ms];
ll a[ms];

void build(int l, int r, int v = 0) {
    if (l == r) {
        seg[v] = Node(a[l]);
    } else {
        int m = (l + r) / 2;
        build(l, m, v * 2 + 1);
        build(m + 1, r, v * 2 + 2);
        seg[v] = Node::merge(seg[v * 2 + 1], seg[v * 2 + 2]);
    }
}

void push(int v, int l, int r) {
    int left = v * 2 + 1;
    int right = v * 2 + 2;
    seg[left].apply(lazy[v]);
    lazy[left].compose(lazy[v]);
    seg[right].apply(lazy[v]);
    lazy[right].compose(lazy[v]);
    lazy[v] = Tag();
}

void update(int a, int b, int l, int r, Tag add, int v = 0) {
    if (b < l or a > r) return;
    if (a <= l and r <= b) {
        seg[v].apply(add);
        lazy[v].compose(add);
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    update(a, b, l, m, add, v * 2 + 1);
    update(a, b, m + 1, r, add, v * 2 + 2);
    seg[v] = Node::merge(seg[v * 2 + 1], seg[v * 2 + 2]);
}

Node query(int a, int b, int l, int r, int v = 0) {
    if (b < l or a > r) return Node();
    if (a <= l and r <= b) return seg[v];
    push(v, l, r);
    int m = (l + r) / 2;
    Node le = query(a, b, l, m, v * 2 + 1);
    Node ri = query(a, b, m + 1, r, v * 2 + 2);
    return Node::merge(le, ri);
}

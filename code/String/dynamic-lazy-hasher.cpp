#include <bits/stdc++.h>
using namespace std;

struct DynamicLazyHasher {
private:
    struct Node {
        array<long long, 2> hash = {0, 0};
        int len = 0;
    };

    const long long mod1 = 188888881, mod2 = 1000000007, base = 137;
    long long invb1, invb2;
    int n;
    
    vector<Node> tree;
    vector<char> lazy;
    vector<long long> p1, p2;

    long long fexp(long long b, long long p, long long mod) {
        long long ans = 1;
        for (; p > 0; p >>= 1) {
            if (p & 1) ans = (ans * b) % mod;
            b = (b * b) % mod;
        }
        return ans;
    }

    Node merge_nodes(const Node& a, const Node& b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;
        
        Node c;
        c.len = a.len + b.len;
        c.hash[0] = (a.hash[0] * p1[b.len] % mod1 + b.hash[0]) % mod1;
        c.hash[1] = (a.hash[1] * p2[b.len] % mod2 + b.hash[1]) % mod2;
        return c;
    }

    void apply(int v, char x) {
        if (x == '\0' || tree[v].len == 0) return;
        long long len = tree[v].len;
        // Soma da PG usando o tamanho nativo do nó
        tree[v].hash[0] = x * (p1[len] - 1 + mod1) % mod1 * invb1 % mod1;
        tree[v].hash[1] = x * (p2[len] - 1 + mod2) % mod2 * invb2 % mod2;
        lazy[v] = x;
    }

    void push(int v) {
        apply(v * 2 + 1, lazy[v]);
        apply(v * 2 + 2, lazy[v]);
        lazy[v] = '\0';
    }

    void build(const string& s, int l, int r, int v) {
        if (l == r) {
            tree[v].len = 1;
            tree[v].hash = {s[l], s[l]};
        } else {
            int mid = l + (r - l) / 2;
            build(s, l, mid, v * 2 + 1);
            build(s, mid + 1, r, v * 2 + 2);
            tree[v] = merge_nodes(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void range_update(int ql, int qr, int l, int r, char x, int v) {
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            apply(v, x);
        } else {
            push(v);
            int mid = l + (r - l) / 2;
            range_update(ql, qr, l, mid, x, v * 2 + 1);
            range_update(ql, qr, mid + 1, r, x, v * 2 + 2);
            tree[v] = merge_nodes(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    Node query(int ql, int qr, int l, int r, int v) {
        if (ql > qr || qr < l || ql > r) return Node(); // Node vazio com len = 0
        if (ql <= l && r <= qr) return tree[v];
        
        push(v);
        int mid = l + (r - l) / 2;
        return merge_nodes(query(ql, qr, l, mid, v * 2 + 1),
                           query(ql, qr, mid + 1, r, v * 2 + 2));
    }

public:
    DynamicLazyHasher(const string& s) {
        n = s.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, '\0');
        p1.resize(n + 1);
        p2.resize(n + 1);
        
        p1[0] = p2[0] = 1;
        for (int i = 1; i <= n; i++) {
            p1[i] = (p1[i - 1] * base) % mod1;
            p2[i] = (p2[i - 1] * base) % mod2;
        }
        
        invb1 = fexp(base - 1, mod1 - 2, mod1);
        invb2 = fexp(base - 1, mod2 - 2, mod2);
        
        if (n > 0) build(s, 0, n - 1, 0);
    }

    // O(log N) - Atualiza o intervalo [l, r] com o caractere 'c'
    void update(int l, int r, char c) {
        if (l > r) return;
        range_update(l, r, 0, n - 1, c, 0);
    }

    // O(log N) - Retorna o hash da substring [l, r]
    array<long long, 2> get_hash(int l, int r) {
        if (l > r) return {-1, -1};
        return query(l, r, 0, n - 1, 0).hash;
    }

    // O(log N) - Checa se [l, r] possui um período de tamanho 'd'
    bool check_period(int l, int r, int d) {
        if (r - l + 1 < d) return false;
        return get_hash(l, r - d) == get_hash(l + d, r);
    }
};

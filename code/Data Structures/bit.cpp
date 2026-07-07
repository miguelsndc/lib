struct BIT {
    int n; vector<ll> bit;
    BIT(int n = 0) : n(n), bit(n + 1, 0) {}
    void add(int i, int v = 1) { for (++i; i <= n; i += i & -i) bit[i] += v; }
    ll sum(int i) const { ll s = 0; for (++i; i > 0; i -= i & -i) s += bit[i]; return s; }
};

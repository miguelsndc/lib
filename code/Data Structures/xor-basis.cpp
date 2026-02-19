template<int N>
struct XorBasis {
    ll rep[N], rank = 0;
    base() {
        memset(rep, 0, sizeof rep);
    }
    void add(ll x) {
        for (int b = N - 1; b >= 0; b--)
            if (x & (1ll << b)) {
                if (rep[b] == 0) {
                    rep[b] = x;
                    rank++;
                    return;
                }
                x ^= rep[b];
            }
    }
    bool depende(ll x) {
        for (int b = N - 1; b >= 0; b--)
            if (x & (1ll << b)) {
                if (rep[b] == 0) return false;
                x ^= rep[b];
            }
        return true;
    };
}
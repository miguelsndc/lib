ll nthTermAP(ll a, ll d, int n) {
    return a + (n - 1) * d;
}

ll sumAP(ll a, ll d, int n) {
    return (n / 2LL) * (2LL * a + (n - 1) * d);
}

ll nthTermGP(ll a, ll r, int n) {
    return a * pow(r, n - 1);
}

ll sumGP(ll a, ll r, int n) {
    if (r == 1) return a * n; // Special case for r=1
    return a * (1 - pow(r, n)) / (1 - r);
}

// calcula n C r mod p (p primo) em log_p(max(n, r))
ll lucas(ll n, ll r, ll p) {
    ll res = 1;
    while (n > 0 || r > 0) {
        ll ni = n % p, ri = r % p;
        if (ri > ni) return 0;
        // precalculado n C R mod p
        // pode ser feito via modulo tbm em log, dai fica log^2
        res = (res * C[ni][ri][p]) % p;
        n /= p; r /= p;
    }
    return res;
}
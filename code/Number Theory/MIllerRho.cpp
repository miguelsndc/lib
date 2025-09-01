#include <bits/stdc++.h>
using namespace std;
#define ll long long

// O(1)
ll fmul(ll a, ll b, ll M) {
    ll k = a * b - M * (long long)(1.L / M * a * b);
    return k + M * (k < 0) - M * (k >= (ll)M);
}

// O(log(e))
ll fexp(ll b, ll e, ll MOD) {
    ll ans = 1;
    while (e) {
        if (e & 1) ans = fmul(ans, b, MOD);
        b = fmul(b, b, MOD);
        e >>= 1;
    }
    return ans;
}

// ~ O(log n)
bool isPrime(ll n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ll bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
       s = __builtin_ctzll(n - 1), d = n >> s;

    for (ll base : bases) {
        ll p = fexp(base % n, d, n), i = s;

        while (p != 1 && p != n - 1 && base % n && i--)
            p = fmul(p, p, n);

        if (p != n - 1 && i != s) return false;
    }
    return true;
}

// O(n^(1/4))
ll rho(ll n) {
    ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](ll x) { return fmul(x, x, n) + i; };
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = fmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

// O(n^(1/4))
vector<ll> factor(ll n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ll x = rho(n);
    auto l = factor(x), r = factor(n / x);
    for (ll x : r) l.push_back(x);
    return l;
}

void solve() {
    ll N;
    cin >> N;
    if (factor(N).size() == 20) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using pll = pair<ll ,ll>;
#define sz(x) ((int)(x).size())

inline ll fix(ll x, ll mod) {x %= mod; if (x < 0) x += mod; return x;}
inline long long LCM(long long a, long long b) { return a / __gcd(a, b) * b; }

struct mdc { ll x, y, d; };
mdc euclides_ext(ll a, ll b) {
    if (b == 0) return {1, 0, a};
    mdc p = euclides_ext(b, a % b);
    return {p.y, p.x - a / b * p.y, p.d};
}

pll crt(vector<pll> congruences) {
    for (auto &[x, y]: congruences) x = fix(x, y);
    auto [ans, lcm] = congruences[0];
    for (int i = 1; i < sz(congruences); i++) {
        auto [a, n] = congruences[i];
        auto [x, y, d] = euclides_ext(lcm, n);
        if ((a - ans) % d != 0) return {-1, -1};
        ans = fix(ans + x * (a - ans) / d % (n / d) * lcm, lcm * n / d);
        lcm = lcm * n / d;
    }
    return {ans, lcm};
}

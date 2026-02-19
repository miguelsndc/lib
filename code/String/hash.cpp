/*
    Double Polynomial Hashing
    Prehcalculo - O(n)
    Substring hash queries - O(1)
    Hash(l, m - 1) calcula o hash da substring incluindo o l de tamanho m
*/

const int MOD1 = 188'888'881;
const int MOD2 = 1e9 + 7;
const int base = 137;

ll pow1[MAXN];
ll pow2[MAXN];

// O(n) - Chamar antes
void calc_pow() {
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        pow1[i] = (pow1[i - 1] * base) % MOD1,
        pow2[i] = (pow2[i - 1] * base) % MOD2;
}

struct Hashing {
    vector<pair<ll, ll>> pref;
    // O(1)
    Hashing(string &s) {
        pref = vector<pair<ll, ll>>(s.size() + 1, {0, 0});
        for (int i = 0; i < s.size(); i++)
            pref[i + 1].first = ((pref[i].first * base) % MOD1 + s[i]) % MOD1,
                     pref[i + 1].second = ((pref[i].second * base) % MOD2 + s[i]) % MOD2;
    }

    // O(1)
    ll operator()(int a, int b) {
        ll h1 = (MOD1 + pref[b + 1].first - (pref[a].first * pow1[b - a + 1]) % MOD1) % MOD1;
        ll h2 = (MOD2 + pref[b + 1].second - (pref[a].second * pow2[b - a + 1]) % MOD2) % MOD2;
        return (h1 << 32) | h2;
    }
};

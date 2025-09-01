/*
    Fast Exponentiation
    Calcula a^b mod m em O(log(n))
*/

ll fexp(ll a, ll b, ll MOD){
    ll ans = 1;
    while(b) {
        if(b & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

/*
Calcula o Inverso Modular de um numero `a` mod `p`
pelo pequeno teorema de fermat.
*/

ll inv(ll a, ll p){ 
    return fexp(a, p - 2);
}

/*
    Calcula N escolhe K mod P
*/

ll fact[1000000]; // Preh computar fatoriais
ll comb(ll n, ll k, ll p) {
    return ((fact[n] * inv(fact[k], p) % p) * inv(fact[n - k], p)) % p;
}


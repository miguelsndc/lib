/*
    Set Xor Min/Max
    
    C = maior valor
    insere um numero em log(C)
    faz a query de um numero descendo na trie em log(C)

    pra pegar o menor/maior xor desse numero com os outros em log
*/

const int mxbit = 32;
const int mxn = 2e5 + 5;

int trie[mxbit * mxn][2], z = 1;
memset(trie[0], -1, sizeof trie);

auto insert = [&] (int x, int msb) {
    bool val; int cur = 0;
    for (int b = msb; b >= 0; b--) {
        val = x & (1 << b);
        if (trie[cur][val] == -1) { 
            memset(trie[z], -1, sizeof trie[z]);
            trie[cur][val] = z++;
        }
        cur = trie[cur][val];
    }
};

auto query = [&] (int x, int msb)->int {
    bool val; int cur = 0,  res = 0;
    for (int b = msb; b >= 0; b--) {
        val = x & (1 << b);
        // troca os dois ifs pra fazer xor min
        if (trie[cur][!val] != -1) cur = trie[cur][!val], res |= (1 << b);
        else if (trie[cur][val] != -1) cur = trie[cur][val];
    }
    return res;
};

const int MAXN = 2e5 + 5; 
const long long M1 = 188888881, M2 = 1e9 + 7, B = 137;
long long p1[MAXN], p2[MAXN];

void calc_pow() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p1[i] = p1[i - 1] * B % M1;
        p2[i] = p2[i - 1] * B % M2;
    }
}

struct Hash {
    vector<long long> h1, h2;
    Hash(string& s) : h1(s.size() + 1), h2(s.size() + 1) {
        for (int i = 0; i < s.size(); i++) {
            h1[i + 1] = (h1[i] * B + s[i]) % M1;
            h2[i + 1] = (h2[i] * B + s[i]) % M2;
        }
    }
    long long get(int l, int r) {
        long long a = (M1 + h1[r + 1] - h1[l] * p1[r - l + 1] % M1) % M1;
        long long b = (M2 + h2[r + 1] - h2[l] * p2[r - l + 1] % M2) % M2;
        return (a << 32) | b;
    }
};

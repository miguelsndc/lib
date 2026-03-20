struct Matrix {
    int n;
    vector<vector<i64>> m;
    Matrix(int n) : n(n), m(n, vector<i64>(n, 0)) {}
    Matrix mul(const Matrix& other, i64 mod) const {
        assert(n == other.n);
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!m[i][k]) continue;
                for (int j = 0; j < n; j++) {
                    res.m[i][j] = (res.m[i][j] + (m[i][k] * other.m[k][j]) % mod) % mod;
                }
            }
        }
        return res;
    }
    Matrix fexp(i64 b, i64 mod) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) res.m[i][i] = 1; 
        Matrix base = *this;
        while (b > 0) {
            if (b & 1) res = res.mul(base, mod);
            base = base.mul(base, mod);
            b >>= 1;
        }
        return res;
    }
};

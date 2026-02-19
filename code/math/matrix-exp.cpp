/*
    Exponenciacao Rapida de Matrizes  O(m³ log (b))
    Calcula recorrências lineares
*/
typedef vector<vector<i64>> matrix;

matrix init(int size) {
    matrix mat(size, vector<i64>(size));
    return mat;
}

vector<i64> vecmul(matrix m, vector<i64> vec, i64 sz, i64 mod) {
    assert(vec.size() == sz);
    vector<i64> ans;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; i++) {
            ans[i] += (vec[j] * (m[i][j]));
        }
    }
    return ans;
}

matrix matmul(matrix m1, matrix m2, i64 mod, i64 sz) {
    matrix ans;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < sz; k++) {
                ans[i][j] = (ans[i][j] + 1LL * (m1[i][k] % mod) * (m2[k][j] % mod)) % mod;
            }
        }
    }
    return ans;
}

// O(log(b))
matrix fexp(matrix p, i64 b, i64 mod, i64 sz) {
    matrix ans;
    for(int i = 0; i < sz; i++) ans[i][i] = 1;
    while(b){
        if(b & 1) ans = matmul(ans, p, mod, sz);
        p = matmul(p, p, mod, sz);
        b >>= 1;
    }
    return ans;
}

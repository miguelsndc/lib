int gauss(int n, int m, vector<vector<int>> &mat) {
    int posto = 0;
    for (int col = 0, row = 0; col < m and row < n; col++) {
        int pivo = -1;
        for (int i = row; i < n; i++) {
            if (mat[i][col] != 0) {
                pivo = i;
                break;
            }
        }
        if (pivo == -1) continue;
        swap(mat[row], mat[pivo]);
        ll invp = inv(mat[row][col]);
        for (int j = col; j < m; j++) mat[row][j] = (mat[row][j] * invp) % mod;
        for (int i = 0; i < n; i++) {
            if (i == row) continue;
            ll fac = mat[i][col];
            for (int j = col; j < m; j++) {
                mat[i][j] = (mat[i][j] - fac * mat[row][j]) % mod;
                if (mat[i][j] < 0) mat[i][j] += mod;
            }
        }
        row++;
        posto = row;
    }
    return posto;
};
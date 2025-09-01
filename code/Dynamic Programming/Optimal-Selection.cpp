/*
    Optimal Selection
    Tens n escolhas pra fazer em k intervalos de tempo,
    escolhe o melhor subconjunto tal que alguma heuristica
    eh maximizada ao longo de todos os timestamps
*/

int optimal_selection(int n, int k, int w[][]) {
   int f[(1 << n)][n + 1];
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            f[i][j] = 0;
        }
    }
    for (int i = 0; i < k; i++) {
        f[(1 << i)][0] = w[i][0];
    }
    for (int day = 1; day < n; day++) {
        for (int mask = 0; mask < 8; mask++) {
            f[mask][day] = f[mask][day - 1];
            for (int y = 0; y < k; y++) {
                if (mask & (1 << y)) {
                    f[mask][day] = max(f[mask][day], f[mask^(1 << k)][day - 1] + w[k][day]);
                }
            }
        }
    }
    return f[(1 << n) - 1][n - 1];
}
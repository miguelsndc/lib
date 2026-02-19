/*
	Range (Idempotent Function) Query
	Build - O(n log n)
	Query - O(1)
	Nao suporta updates, para queries de funcoes tipo soma eh melhor so usar uma seg mesmo
	Testado em: https://judge.yosupo.jp/problem/staticrmq
*/

template<typename T> class SparseTable {
    private:
        int n, k;
        vector<vector<T>> st;
    public: 
    SparseTable(const vector<T> & v) {
        n = v.size(); k = 31 - __builtin_clz(n) + 1;
        st.resize(k); st[0] = v;
        for (int i = 1; i < k; i++) {
            st[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; j++) 
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    T query(int l, int r) {
        int p = 31 - __builtin_clz(r - l + 1);
        return min(st[p][l], st[p][r - (1 << p) + 1]);
    }
};

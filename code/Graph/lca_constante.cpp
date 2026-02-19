/*
    Least Common Ancestor in a Tree
    Computa o menor ancestral de dois nodes a e b 
    tbm suporta queries de distancia entre dois nodes

    testado em: https://cses.fi/problemset/result/12501773/ e https://cses.fi/problemset/task/1135
*/

template<typename T>
class LCA {
    private:
        int n; const vector<vector<T>> &g;
        SparseTable<pair<T, T>> rmq;
        vector<T> tin, et, depth;
        int timer = 0;

        // O(n)
        void dfs(int u = 0, int p = -1) {
            tin[u] = timer;
            et[timer++] = u;
            for (int v: g[u]) {
                if (v != p) {
                    depth[v] = depth[u] + 1;
                    dfs(v, u);
                    et[timer++] = u;
                }
            }
        }

    public: 
        // Build O(nlogn)
        LCA(vector<vector<T>> & _g): n(_g.size()), g(_g), tin(n), et(2 * n), depth(n), rmq(vector<pair<T ,T>>(1)) {
            dfs();
            vector<pair<T, T>> arr(2 * n);
            for (int i = 0; i <  2 * n; i++) {arr[i] = {depth[et[i]], et[i]}; };
            rmq = SparseTable<pair<T, T>>(arr);
        }

        // O(1)
        T query(int a, int b) {
            if (tin[a] > tin[b]) swap(a, b);
            return rmq.query(tin[a], tin[b]).second;
        }

        // O(1)
        T dist(int a, int b) {
            return depth[a] + depth[b] - 2 * depth[query(a, b)];
        }
};


/*
    Fenwick Tree - Range Queries
*/

template <typename T = int>
struct FenwickTree {
    vector<T> bit(maxn), arr(maxn);

    // O(log(n))
    void add(int pos, int val) {
        for (int i = pos + 1; i < maxn; i += (i & (-i))) bit[i] += val;
    }

    // O(log(n))
    void pset(int pos, int val) {
        int delta = val - arr[pos];
        arr[pos] = val;
        add(pos, delta);
    }

    // O(log(n))
    T query(int pos) {
        T sum = 0;
        for (int i = pos + 1; i > 0; i -= (i & (-i))) sum += bit[i];
        return sum;
    }
};
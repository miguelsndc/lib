#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;
constexpr int mod = 1e9 + 7, maxn = 1e5 + 5;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct node {
    int cnt, weight, left, right;
    i64 sum = 0;
    int val, neg;
    node (int v): cnt(1), weight(rng()), left(-1), right(-1), sum(v), val(v), neg(0) {}
};

vector<node> tree;

void push_lazy(int i) {
    if (tree[i].neg) {
        tree[i].val *= -1;
        tree[i].sum *= -1;
        tree[i].neg = 0;
        // resolve lazy negations and push to children
        if (tree[i].left >= 0) tree[tree[i].left].neg ^= 1;
        if (tree[i].right >= 0) tree[tree[i].right].neg ^= 1;
    }
}

// subtree size
int cnt(int i) { return i == -1 ? 0 : tree[i].cnt; };

i64 sum(int i) {
    if (i >= 0 and tree[i].neg) push_lazy(i);
    return i == -1 ? 0 : tree[i].sum;
}

void flip(int i) {
    tree[i].neg ^= 1;
    push_lazy(i);
}

void update_cnt(int i) { 
    tree[i].cnt = 1 + cnt(tree[i].left) + cnt(tree[i].right);
    tree[i].sum = tree[i].val + sum(tree[i].left) + sum(tree[i].right);
}

// split treap at index k
void split(int n, int k, int &l ,int &r) {
    if (n == -1) { l = r = -1; return; }
    push_lazy(n); // always resolve pending lazy udpates before opreations
    if (cnt(tree[n].left) < k) {
        split(tree[n].right, k - cnt(tree[n].left) - 1, tree[n].right, r), l = n;
    } else {
        split(tree[n].left, k, l, tree[n].left), r = n;
    }
    update_cnt(n);
}

void merge(int l, int r, int &n) {
    if (l == -1 || r == -1) {n = (l == -1 ? r : l); return; }
    push_lazy(l), push_lazy(r); // reoslve pending
    if (tree[l].weight > tree[r].weight) {
        merge(tree[l].right, r, tree[l].right), n = l;
    } else {
        merge(l, tree[r].left, tree[r].left), n = r;
    }
    update_cnt(n);
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    i64 cur_sum = 0;
    int rt = -1; 
    for (int i = 0; i < n; i++) {
        cur_sum += i % 2 == 1 ? -a[i] : a[i];
        tree.push_back(node(i % 2 == 1 ? -a[i] : a[i]));
        merge(rt, tree.size() - 1, rt);
    }
    while(q--) {
        int l, r; cin >> l >> r; --l, --r;
        int left, mid, right;
        // mid = [0, r] right -> [r + 1, ]
        split(rt, r + 1, mid, right);
        // left -> [0, l - 1] mid [l, r]
        split(mid, l, left, mid);
        // take off the sum of mid interval
        cur_sum -= sum(mid);
        int k, shift;
        // k [0, 1] shift [1, r]
        split(mid, 1, k, shift);
        // flip signs odd -> even and even -> odd because of shifting
        flip(shift);
        if (l % 2 != r % 2) flip(k);
        // merge [shift, k] into mid
        merge(shift, k, mid);
        // merge and add sum back
        cur_sum += sum(mid);
        // merge left and mid into rt
        merge(left, mid, rt);
        // merge rt and right into rt'
        merge(rt, right, rt);
        if (cur_sum > 0) cout << "FISH\n";
        else if (cur_sum == 0) cout << "TIE\n";
        else cout << "MAN\n";
    }
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1; // cin >> tt;
    while(tt--) {
        solve();
    }
}
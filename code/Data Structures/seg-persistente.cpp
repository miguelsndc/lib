    #include <bits/stdc++.h>
using namespace std;
const int ms = 5e5 + 5, inf = 1e9 + 1, MAX_NODES = 1e7+1;
struct Node {
    int val = 0;;
    Node *l, *r;
    Node() : val(0), l(nullptr), r(nullptr) {}
    Node (int x): val(x), l(nullptr), r(nullptr) {}
    Node (Node *ll, Node *rr) {
        l = ll, r = rr;
        val = 0;
        if (l) val += l->val;
        if (r) val += r->val;
    }
    Node(Node *cp): val(cp->val), l(cp->l), r(cp->r) {}
    void *operator new(size_t);
};
int mem_ptr=0;
Node pool[MAX_NODES];
Node* roots[ms];
void *Node::operator new(size_t) {
    return &pool[mem_ptr++];
}
Node *update(Node *node, int pos, int l, int r) {
    if (l == r) {
        int count = node ? node->val : 0;
        return new Node(count + 1);
    }
    int mid = (l + r) / 2;
    Node *le = node ? node->l : nullptr;
    Node *ri = node ? node->r : nullptr;
    if (pos > mid) {
        auto novo = update(ri, pos, mid + 1, r);
        return new Node(le, novo);
    }
    auto novo = update(le, pos, l, mid);
    return new Node(novo, ri);
}

int query(Node *rootl, Node*rootr, int l, int r, int k) {
    if (l == r) return l;
    int mid = l + (r - l) / 2;
    int cnt_l = (rootl and rootl->l) ? rootl->l->val : 0;
    int cnt_r = (rootr and rootr->l) ? rootr->l->val : 0;
    int cnt_left = cnt_r - cnt_l;
    if (cnt_left >= k) {
        return query(rootl ? rootl->l: nullptr, rootr ? rootr->l : nullptr, l, mid, k);
    }
    return query(rootl ? rootl->r : nullptr, rootr ? rootr->r : nullptr, mid + 1, r, k - cnt_left);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;cin>>n>>m;
    vector<int> a(n+1), vals;
    for (int i=1;i<=n;i++) cin >> a[i], vals.emplace_back(a[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    auto get=[&](int x) {
        return lower_bound(vals.begin(),vals.end(),x)-vals.begin()+1;
    };
    int mx=(int)vals.size();
    map<int,int>rev;
    for (int i=1;i<=n;i++)rev[get(a[i])]=a[i];
    roots[0]=nullptr;
    for (int i=1;i<=n;i++){
        roots[i] = update(roots[i-1],get(a[i]),1,mx); 
    }
    while(m--){
        int l,r,k;cin>>l>>r>>k;
        int v = query(roots[l-1],roots[r],1,mx,k);
        cout<<rev[v]<<'\n';
    }
}

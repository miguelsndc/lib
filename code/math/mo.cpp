#include <bits/stdc++.h>
using namespace std;
const int BLOCK = 350; // ajuste para ~sqrt(N)
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = 1LL << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    return ans + ((seg == 1 || seg == 2) ? add : (subSquareSize - add - 1));
}

struct Query {
    int l, r, id;
    int64_t ord; // use se hilbert
    inline void calc_hilbert() { ord = hilbertOrder(l, r, 21, 0); } // use se hilbert
    bool operator<(const Query& o) const {
        int b1 = l / BLOCK, b2 = o.l / BLOCK;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < o.r) : (r > o.r); 
    }
};

void add(int i) {} 
void remove(int i)
int get_ans()

void mo(vector<Query>& queries) {
    // for (auto& q : queries) q.calc_hilbert();
    // sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
    //     return a.ord < b.ord;
    // });

    sort(queries.begin(), queries.end());
    
    int L = 0, R = -1; 
    for (auto& q : queries) {
        while (L > q.l) add(--L);
        while (R < q.r) add(++R);
        while (L < q.l) remove(L++);
        while (R > q.r) remove(R--);
        
        ans[q.id] = get_ans();
    }
}

l#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e6 + 5;
int n, a[maxn], lc[maxn], rc[maxn], par[maxn];
void cartesian_tree() {
    stack<int> st;
    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!st.empty()) {
            int x = st.top();
            // < para min-heap > para max-heap  
            if (a[x] < a[i]) break;
            st.pop();
            last = x;
        }
        if (last != -1) {
            lc[i] = last;
            par[last] = i;
        }
        if (!st.empty()) { rc[st.top()] = i, par[i] = st.top(); }
        st.push(i);
    }
}
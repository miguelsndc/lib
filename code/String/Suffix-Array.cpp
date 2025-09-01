/*
    Suffix Array
    Constrói o suffix array e o lcp array em O(n log n) pro sa + O(n) pro lcp
*/


vector<int> build_sa(string &s) {
    s += '$';
    int n = s.size();
    const int ALPHA = 256;
    vector<int> p(n), c(n), cnt(max(ALPHA, n));
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < ALPHA; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0; int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0; 
        int new_classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev) ++new_classes;
            cn[p[i]] = new_classes - 1;
        }
        c.swap(cn);
        swap(classes, new_classes);
    }
    s.pop_back();
    p.erase(p.begin());
    return p;
}

vector<int> build_lcp(string &s, vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    vector<int> lcp(n - 1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0; continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}

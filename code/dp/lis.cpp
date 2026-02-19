/*
    Longest Increasing Subsequence
    Encontra o tamanho e recupera uma LIS de um vetor `a`
    Complexidade: O(n log n)
*/

vector<int> lis(vector<int> const& a) {
    int n = a.size();
    vector<int> d(n+1, INF), pos(n+1, -1), prev(n, -1);    
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        int l = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (a[i] < d[l]) {
            d[l] = a[i];
            pos[l] = i;
            prev[i] = pos[l-1];
        }
    }

    int len = 0;
    while (d[len] < INF) {
        len++;
    }
    len--; 

    vector<int> result;
    int curr_pos = pos[len];
    while (curr_pos != -1) {
        result.push_back(a[curr_pos]);
        curr_pos = prev[curr_pos];
    }
    reverse(result.begin(), result.end()); 

    return result; 
}


/*
Dijkstra - Single Source Shortest Path
Complexidade O(n log (n))
*/
vector<ll> dist(maxn, INF);
vector<pii> g[maxn];
vector<ll> dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii>> pq; 
    pq.push({0, 0});
    dist[0] = 0;
    while(!pq.empty()) {
        auto [cost, from] = pq.top();
        pq.pop();
        if (dist[from] != cost) continue;
        for (const auto&[w, to]: g[from]) {
            if (dist[from] + w < dist[to]) {
                dist[to] = dist[from] + w;
                pq.push({dist[to], to });
            }
        }
    }
    return dist;
}
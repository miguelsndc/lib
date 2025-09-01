/*
    Kahn Topological Sorting
    Complexidade - O(V + E)

    Encontra a ordenacao topologica e detecta ciclos ao 
    mesmo tempo
*/
vector<int> KahnToposort(int n, vector<int> *graph) {
    vector<int> in_degree(n);
    for (int i = 0; i < n; i++) {
        for (int to : graph[i]) {
            in_degree[to]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }

    int idx = 0;
    vector<int> order(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order[idx++] = u;
        for (int v: graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (idx != n) {
        return {};  // cycle detected
    }

    return order;
}


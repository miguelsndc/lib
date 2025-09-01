/*
    Floyd Warshall - All Pairs Shortest Path
    Funciona apenas em matrizes
    Complexidade O(n³)
*/

vector<vector<ll>> FloydWarshall(int n, vector<vector<int>> &graph) {
    // precomputa distâncias O(n²)
    vector<vector<ll>> distance(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
            distance[i][j] = 0;
            } else if (graph[i][j] != -1) { 
                distance[i][j] = graph[i][j];
            }
        }
    }

    // O(n³)
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }
}
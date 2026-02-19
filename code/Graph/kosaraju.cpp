/*
    Kosaraju's algorithm
    Find strongly connected components in a directed graph in O(n)
    with two dfs passes
*/
#include <bits/stdc++.h>
using namespace std;

class Kosaraju {
    private:
        const int n;
        vector<bool> visited;
    public:

    vector<int> dfs(int v, vector<vector<int>> &adj, vector<int> &output) {
        visited[v] = true;
        for (auto u: adj[v]) {
            if (!visited[u]) dfs(u, adj, output);
        }
        output.push_back(v);
    }

    vector<vector<int>> scc(vector<vector<int>> & adj, vector<vector<int>> &adj_transp) {
        int n = adj.size();
        vector<vector<int>> components; 
        vector<int> order; visited.assign(n, false);
        for (int i = 0; i < n; i++) {
            if(!visited[i]) dfs(i, adj, order);
        }
        visited.assign(n, false);
        reverse(order.begin(), order.end());
        for (int v: order) {
            if (!visited[v]) {
                vector<int> component;
                dfs(v, adj_transp, component);
                components.push_back(component);
            }
        }
        return components;
    }
};
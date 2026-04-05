#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
struct Node {
    int fail = 0, exit = 0, parent = 0;
    array<int, 26> next = {};
    vector<int> end;
};
struct AhoCorasick {
    vector<Node> trie;
    vector<int> bfs_order;
    AhoCorasick() {
        trie.emplace_back();
    }
    void insert(string& s, int idx) {
        int node = 0;
        for (char c : s) {
            int j = c - 'a';
            if (trie[node].next[j] == 0) {
                trie[node].next[j] = sz(trie);
                trie.emplace_back();
            }
            node = trie[node].next[j];
        }
        trie[node].end.push_back(idx);
    }
    void resolve_links() {
        queue<int> q;
        for (int j = 0; j < 26; j++) {
            int node = trie[0].next[j];
            if (node != 0) q.push(node);
        }
        while (not q.empty()) {
            int node = q.front();
            q.pop();
            bfs_order.push_back(node);
            int fail = trie[node].fail;
            if (not trie[fail].end.empty()) {
                trie[node].exit = fail;
            } else {
                trie[node].exit = trie[fail].exit;
            }
            for (int j = 0; j < 26; j++) {
                int c = trie[node].next[j];
                if (c != 0) {
                    trie[c].fail = trie[fail].next[j];
                    q.push(c);
                } else {
                    trie[node].next[j] = trie[fail].next[j];
                }
            }
        }
    }
    void match(string& t, vector<int> &ans) {
        vector<int> freq(sz(trie));
        int node = 0;
        for (char c: t) {
            node = trie[node].next[c - 'a'];
            freq[node]++;
        }
        for (int i = sz(bfs_order) - 1; i >= 0; i--) {
            int u = bfs_order[i];
            if (freq[u] > 0) {
                freq[trie[u].fail] += freq[u];
            }
        }
        for (int u = 0; u < sz(trie); u++) {
            if (freq[u] > 0) {
                for (int m: trie[u].end) {
                    ans[m] += freq[u];
                }
            }
        }
    }
};

#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
    Knapsack Problem -
    Given a set of items with value i and cost j, and you have limited budget
    find the subset of items you can take where total value is maximal
    Variations covered:
        - 0/1 Knapsack - Only one copie of each item can be taken
        - Bounded Knapsack - Each item has a number k[i] of copies
    
    If item retrieval is unecessary prefer 1D knapsack
*/

/*
    0/1 Knapsack - One copy of each item
*/

int f[n + 1][cap + 1], weight[n], value[n];

// Time: O(nW)
// Space : O(nW)
int knapsack_2D() {
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            f[i][w] = f[i - 1][w];
            if (w >= weight[i - 1]) {
                f[i][w] = max(f[i][w], f[i - 1][w - weight[i - 1]] + value[i - 1]);
            }
        }
    }
    return f[n][W];
}

// Time O(nW)
// Space O(w)
int knapsack_1D() {
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= weight[i]; i--) {
            f[w] = max(f[w], f[w - weight[i]] + value[i]);
        }
    }
    return f[W];
}

/*
Unbounded Knapsack - Infinite copies of each item
*/

// Time O(nW)
// Space O(nw)
int unbounded_knapsack_2D() {
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            f[i][w] = f[i - 1][w];  // Not taking item
            if (w >= weight[i - 1]) {
                f[i][w] = max(f[i][w], f[i][w - weight[i - 1]] + value[i - 1]);
            }
        }
    }
    return f[n][W];
}

// Time O(nW)
// Space O(W)
int unbounded_knapsack_1D() {
    for (int i = 0; i < n; i++) {
        for (int w = weight[i]; w <= W; w++) {  // Forward loop allows reuse
            f[w] = max(f[w], f[w - weight[i]] + value[i]);
        }
    }
    return f[W];
}

/*
    Bounded knapsack - Bounded number of copies of each item
*/

// Time: O(nWk) suitable for small k
// Space: O(nW)
int bounded_knapsack_2D() {
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            f[i][w] = f[i - 1][w];  // Not taking item
            for (int k = 1; k <= count[i - 1] && k * weight[i - 1] <= w; k++) {
                f[i][w] = max(f[i][w], f[i - 1][w - k * weight[i - 1]] + k * value[i - 1]);
            }
        }
    }
    return f[n][W];
}

// Time: O(nW) any k
// Space: O(W)
int bounded_knapsack_1D() {
    for (int i = 0; i < n; i++) {
        for (int k = 1; count[i] > 0; k *= 2) {
            int take = min(k, count[i]);
            count[i] -= take;
            for (int w = W; w >= take * weight[i]; w--) {
                f[w] = max(f[w], f[w - take * weight[i]] + take * value[i]);
            }
        }
    }
    return f[W];
}
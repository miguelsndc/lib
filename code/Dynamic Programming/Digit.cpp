#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
Digit DP 
Calcula a soma dos digitos de todos os numeros entre 0 e `number`
para intervalo [a, b] -> solve(b) - solve(a - 1)
*/

const int MAX_DIGITS = 10;
ll dp[MAX_DIGITS][180][2];
vector<int> number;
ll f(int pos, ll sum, int smaller) {
    if (pos == number.size()) return sum;
    ll &ans = dp[pos][sum][smaller];
    if (~ans) return ans;
    ans = 0;
    for (int i=0; i <= (smaller ? 9: number[pos]); i++) {
        bool smaller_now = (smaller || i < number[pos]);
        ans += f(pos + 1, sum + i, smaller_now);
    }
    return dp[pos][sum][smaller] = ans;
}

/*

    Se nao tiver inversa:
    const int MAX_DIGITS = 20;
    const int MAX_K = 20;
    ll dp[MAX_DIGITS][MAX_K][2][2]; // 

    int d, k;
    vector<int> number_a, number_b;

    ll solve(int pos, int cnt, bool smaller_than_b, bool greater_than_a){
        if(pos == number_a.size()) return (cnt == k);
        ll &ans = dp[pos][cnt][smaller_than_b][greater_than_a];
        if(~ans) return ans;
        ans = 0;
        for(int i = (greater_than_a ? 0 : number_a[pos]); i <= (smaller_than_b ? 9 : number_b[pos]); i++){
            bool is_smaller_now = (smaller_than_b || (i < number_b[pos]));
            bool is_greater_now = (greater_than_a || (i > number_a[pos]));
            int new_cnt = cnt + (i == d);
            ans += solve(pos+1, new_cnt, is_smaller_now, is_greater_now);
        }
        return ans;
    }

*/

vector<int> ntovec(int num)  {
    if (num == 0) return {0};
    vector<int> v;
    for (; num >0; num /= 10) v.push_back(num % 10);
    reverse(begin(v), end(v));
    return v;
}

ll solve(int n) {
    if (n < 0) return 0;
    number = ntovec(n);
    memset(dp, -1, sizeof dp);
    return f(0, 0, false);
}

ll ans(int a, int b) {
    return solve(b) - solve(a - 1);
}
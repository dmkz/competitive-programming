#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> vec(n);
    for(int i = 0; i < n; ++i) cin >> vec[i];
    const int INF = int(1e9);
    vector<int> answer(n, INF);
    const int m = 200000;
    std::bitset<m> bst, rev_bst;
    for(int i = 0; i < n; ++i) bst[i] = (vec[i] == 0);
    for(int i = 0; i < m; ++i)
    {
        rev_bst[i] = bst[m - 1 - i];
    }
    
    for(int i = 0; i < n; ++i)
    {
        int next_0 = bst._Find_next(i);
        answer[i] = std::min(answer[i], (next_0 == m) ? INF : next_0 - i);
        if(vec[i] == 0) answer[i] = 0;
    }
    for(int i = 0; i < n; ++i)
    {
        int next_0 = m - 1 - rev_bst._Find_next(m - i - 1);
        answer[i] = std::min(answer[i], (next_0 == -1) ? INF : i - next_0);
        if(vec[i] == 0) answer[i] = 0;
    }
    for(auto &el : answer) cout << el << " ";
}
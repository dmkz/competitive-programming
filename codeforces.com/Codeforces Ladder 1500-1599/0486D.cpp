/*
    Problem: 486D. Valid Sets
    Solution: dfs, trees, combinatorics, dynamic programming, O(n^2)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const int mod = (int)1e9+7;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

int main() {
    ios_fast;
    int diff, n; std::cin >> diff >> n;
    vi arr(n); input(arr);
    vvi edges(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    vi visited;
    std::function<int(int,int)> solve = [&](const int root, const int vert) {
        visited[vert] = 1;
        int answ = 1;
        for (auto next : edges[vert]) {
            if (visited[next]) continue;
            if (arr[next]  < arr[root] || arr[next] > arr[root] + diff) continue;
            if (arr[next] == arr[root] && next < root) continue; // remove duplicates
            visited[next] = 1;
            answ = int(ll(answ) * (1 + solve(root, next)) % mod);
        }
        return answ;
    };
    
    int answ = 0;
    for (int s = 0; s < n; ++s) {
        visited.assign(n, 0);
        answ = (answ + solve(s, s)) % mod;
    }
    std::cout << answ;
    return 0;
}
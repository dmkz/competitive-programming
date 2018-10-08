/*
    Problem: 294A. Shaass and Oskols
    
    Solution: implementation, O(n + m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

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
    int n; std::cin >> n;
    vi cnt(1+n+1); for (int i = 1; i <= n; ++i) std::cin >> cnt[i];
    int m; std::cin >> m;
    while (m--) {
        int pos, line; std::cin >> line >> pos;
        cnt[line-1] += pos-1;
        cnt[line+1] += cnt[line]-pos;
        cnt[line] = 0;
    }
    for (int i = 1; i <= n; ++i) std::cout << cnt[i] << '\n';
    return 0;
}
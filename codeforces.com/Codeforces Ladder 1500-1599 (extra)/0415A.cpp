/*
    Problem: 415A. Mashmokh and Lights
    
    Solution: implementation, O(n)
    
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
    int n, m; std::cin >> n >> m;
    vi answ(n);
    while (m--) {
        int v; std::cin >> v; --v;
        for (int i = v; i < n; ++i) {
            if (!answ[i]) {
                answ[i] = v+1;
            }
        }
    }
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}
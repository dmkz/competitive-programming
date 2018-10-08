/*
    Problem: 262A. Roma and Lucky Numbers
    
    Solution: implementation, O(n log(MAX))
    
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
    int n, k; std::cin >> n >> k;
    int answ = 0;
    while (n--) {
        int val, cur = 0; std::cin >> val;
        do {
            cur += val % 10 == 4 || val % 10 == 7;
            val /= 10;
        } while (val > 0);
        answ += cur <= k;
    }
    std::cout << answ;
    return 0;
}
/*
    Problem: 202A. LLPS
    
    Solution: palindrome, strings, bitmasks, brute force, O(n * 2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <numeric>
#include <cmath>

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
    std::string s; std::cin >> s;
    int n = size(s);
    std::string answ = s.substr(0,1);
    for (int i = 1; i < (1 << n); ++i) {
        std::string t;
        for (int j = 0; j < n; ++j) {
            if (((i >> j) & 1) == 1) {
                t.push_back(s[j]);
            }
        }
        std::string r = t;
        std::reverse(all(r));
        if (r != t) continue;
        answ = std::max(answ, t);
    }
    std::cout << answ;
    return 0;
}
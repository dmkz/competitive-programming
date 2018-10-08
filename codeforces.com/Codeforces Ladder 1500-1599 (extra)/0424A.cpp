/*
    Problem: 424A. Squats
    
    Solution: implementation, strings, O(n)
    
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
    std::string s; std::cin >> s;
    int nStay = 0, pos = 0, answ = 0;
    for (auto& it : s) nStay += (it == 'X');
    while (nStay != n / 2) {
        if (nStay > n / 2) {
            while (pos < n && s[pos] != 'X')++pos;
            assert(pos < n);
            s[pos] = 'x';
            nStay--; ++answ;
        } else {
            while (pos < n && s[pos] != 'x')++pos;
            assert(pos < n);
            s[pos] = 'X';
            nStay++; ++answ;
        }
    }
    std::cout << answ << '\n' << s;
    return 0;
}
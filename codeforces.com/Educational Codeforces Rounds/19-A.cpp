/*
    Problem: 797A. k-Factorization
    
    Solution: implementation, math, number theory, O(sqrt(n))
    
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
    int n,k; std::cin >> n >> k;
    
    vi answ;
    
    for (int i = 2; i * i <= n; ++i) {
        int j = n / i;
        if (n == j * i) {
            while (n % i == 0) {
                answ.push_back(i);
                n /= i;
            }
        }
    }
    
    if (n > 1) {
        answ.push_back(n);
    }
    while (size(answ) > k) {
        answ[size(answ)-2] *= answ[size(answ)-1];
        answ.pop_back();
    }
    if (size(answ) != k) {
        std::cout << -1;
    } else {
        for (auto& it : answ) {
            std::cout << it << ' ';
        }
    }
    
    return 0;
}
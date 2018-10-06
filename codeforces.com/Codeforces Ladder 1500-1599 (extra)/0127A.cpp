/*
    Problem: 127A. Wasted Time
    
    Solution: geometry, O(n)
    
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
    int n, k; std::cin >> n >> k;
    double sum = 0;
    vi x(n), y(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
        if (i > 0) {
            auto dx = x[i]-x[i-1];
            auto dy = y[i]-y[i-1];
            sum += std::sqrt(dx*dx+dy*dy);
        }
    }
    std::cout << std::fixed << std::setprecision(6) << sum * k / 50;
    return 0;
}
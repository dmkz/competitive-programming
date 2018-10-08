/*
    Problem: 246A. Buggy Sorting
    
    Solution: constructive, O(n)
    
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
    if (n == 1 || n == 2) { std::cout << -1; return 0; }
    vi arr(n);
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 1;
    for (int i = 3; i < n; ++i) arr[i] = i+1;
    for (auto& it : arr) std::cout << it << ' ';
    return 0;
}
/*
    Problem: 190D. Non-Secret Cypher
    
    Solution: two pointers, coordinate compression, binary search, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()
#define lowpos(x, y) int(std::lower_bound(all(x), y) - (x).begin())
#define unique(x) (x).erase(std::unique(all(x)), (x).end())

typedef std::vector<int> vi;
typedef long long ll;

ll solve(int n, int k, vi arr) {
    // Coordinate compression:
    vi x;
    for (auto& it : arr) { x.push_back(it); }
    std::sort(all(x));
    unique(x);
    for (auto& it : arr) {
        it = lowpos(x, it);
    }
    // Two pointers:
    vi cnt((int)x.size(), 0);
    int l = 0, r = -1;
    ll answ = 0;
    while (l < n) {
        while (r + 1 < n && cnt[arr[r+1]] + 1 < k) {
            r++;
            cnt[arr[r]]++;
        }
        if (r + 1 < n && cnt[arr[r+1]] + 1 == k) {
            answ += (n - r - 1);
        }
        cnt[arr[l]]--;
        l++;
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, k;
    while (std::cin >> n >> k) {
        vi arr(n); for (auto& it : arr) { std::cin >> it; }
        std::cout << solve(n, k, arr) << std::endl;
    }
    return 0;
}
/*
    Problem: 602B. Approximating a Constant Range
    
    Solution: two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>

const int INF = (int)1e6;

struct Pair {int value, pos;};

bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.pos < b.pos);
}

bool operator>(const Pair& a, const Pair& b) {
    return b < a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::set<Pair, std::less<Pair>> min;
    std::set<Pair, std::greater<Pair>> max;
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    min.insert(Pair{ INF,-1});
    max.insert(Pair{-INF,-1});
    int l = 0, r = -1, answ = 1;
    while (l < n) {
        while (r+1 < n) {
            int tmin = std::min(arr[r+1], min.begin()->value);
            int tmax = std::max(arr[r+1], max.begin()->value);
            if (tmax - tmin <= 1) {
                r++;
                max.insert(Pair{arr[r], r});
                min.insert(Pair{arr[r], r});
            } else break;
        }
        assert(r >= l);
        answ = std::max(answ, r-l+1);
        min.erase(Pair{arr[l],l});
        max.erase(Pair{arr[l],l});
        ++l;
    }
    std::cout << answ;
    return 0;
}
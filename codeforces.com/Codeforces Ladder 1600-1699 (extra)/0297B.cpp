/*
    Problem: 297B. Fish Weight
    
    Solution: coordinate compression, sorting, binary search, greedy, prefix sums, O((n+m)*log(n+m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m, k;
    while (std::cin >> n >> m >> k) {
        // Input lists of weights and compress coordinates:
        std::vector<int> list1(n), list2(m), weight;
        for (auto& it : list1) { std::cin >> it; weight.push_back(it); }
        for (auto& it : list2) { std::cin >> it; weight.push_back(it); }
        std::sort(all(weight));
        weight.erase(std::unique(all(weight)), weight.end());
        // Counting sort for union of list1 and list2:
        const int last = (int)weight.size()-1;
        std::vector<int> cnt1(1+last), cnt2(1+last);
        for (auto w : list1) {
            cnt1[int(std::lower_bound(all(weight), w) - weight.begin())]++;
        }
        for (auto w : list2) {
            cnt2[int(std::lower_bound(all(weight), w) - weight.begin())]++;
        }
        // Greedy checking of win condition:
        ll suff1 = 0, suff2 = 0;
        bool res = false;
        for (int i = last; i >= 0; --i) {
            suff1 += cnt1[i];
            suff2 += cnt2[i];
            if (suff1 > suff2) {
                res = true;
                break;
            }
        }
        std::cout << (res ? "YES" : "NO") << std::endl;
    }
    return 0;
}
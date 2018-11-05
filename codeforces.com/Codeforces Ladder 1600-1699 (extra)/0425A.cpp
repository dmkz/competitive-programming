/*
    Problem: 425A. Sereja and Swaps
    
    Solution: brute force, multiset, O(n^2*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define all(x) (x).begin(), (x).end()

typedef std::vector<int> vi;

const int INF = (int)1e9;

int solve(const int n, const int k, const vi& arr) {
    int answ = -INF;
    for (int pos = 0; pos < n; ++pos) {
        std::multiset<int> inner, outer;
        for (int i = 0; i < n; ++i) {
            outer.insert(arr[i]);
        }
        int sum = 0;
        for (int len = 1; pos + len - 1 < n; ++len) {
            sum += arr[pos+len-1];
            inner.insert(arr[pos+len-1]);
            outer.erase(outer.lower_bound(arr[pos+len-1]));
            int cnt = std::min({(int)inner.size(), (int)outer.size(), k});
            auto it = inner.begin();
            auto jt = outer.rbegin();
            int tmp = sum;
            while (cnt > 0 && *it < *jt) {
                --cnt, tmp += *jt - *it;
                it++,jt++;
            }
            answ = std::max(answ, tmp);
        }
    }
    return answ;
}

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        std::vector<int> arr(n);
        for (auto& it : arr) {
            std::cin >> it;
        }
        std::cout << solve(n,k,arr) << std::endl;
    }
    return 0;
}
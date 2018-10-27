/*
    Problem: 446A. DZY Loves Sequences
    
    Solution: two pointers, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <deque>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; 
    while (std::cin >> n) {
        std::vector<ll> arr(n), diff(n, (ll)2e9);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        for (int i = 1; i < n; ++i) {
            diff[i] = arr[i] - arr[i-1];
        }
        int l = 0, r = 0, answ = 1;
        std::deque<int> negPos;
        while (l+1 < n) {
            // move right border of segment:
            while (r+1 < n && (int)negPos.size() <= 1) {
                r++;
                if (diff[r] <= 0) {
                    negPos.push_back(r);
                }
            }
            // update answer:
            if (negPos.empty()) {
                answ = std::max(answ, r-l+1);
            } else {
                int p = negPos.front();
                if (p == l+1) {
                    answ = std::max(answ, r - l + 2 - (int)negPos.size());
                } else if (p == n-1 || std::max(diff[p+1], diff[p-1]) <= -diff[p]+1) {
                    answ = std::max(answ, p - l + 1);
                } else {
                    answ = std::max(answ, r - l + 2 - (int)negPos.size());
                }
            }
            // move left border of segment:
            ++l;
            if (!negPos.empty() && negPos.front() == l) {
                negPos.pop_front();
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}
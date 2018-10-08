/*
    Problem: 675C. Money Transfers
    
    Solution: prefix sums, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
typedef long long ll;
int main() {
    // Input array:
    int n; scanf("%d", &n);
    std::vector<int> a(2*n);
    for (int i = 0, v; i < n; ++i) {
        scanf("%d", &v); a[i] = a[i+n] = v;
    }
    // Calculate prefix sums:
    std::vector<ll> sum{0};
    for (auto& it : a) {
        sum.push_back(sum.back()+it);
    }
    // Init map of counts of sums in window size n:
    std::map<ll,int> cnt;
    for (int i = 1; i <= n; ++i) {
        cnt[sum[i]]++;
    }
    // Shift window and calculate max answer:
    int max = -1, imax = -1;
    for (int i = 1; i <= n; ++i) {
        int tmp = cnt[sum[i-1]];
        if (tmp > max) {
            max = tmp;
            imax = i-1;
        }
        cnt[sum[i]]--;
        cnt[sum[i+n]]++;
    }
    // Rotate array and calculate finally answer:
    std::rotate(a.begin(), a.begin()+imax, a.end());
    a.resize(n);
    ll balance = 0; int answ = 0, prev = -1;
    for (int i = 0; i < n; ++i) {
        balance += a[i];
        if (balance == 0) {
            answ += i - prev - 1;
            prev = i;
        }
    }
    printf("%d\n", answ);
    return 0;
}
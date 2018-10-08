/*
    Problem: 160C. Find Pair
    
    Solution: binary search, prefix sums, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Input:
    int n; ll need;
    std::cin >> n >> need;
    std::vector<int> item(n), cnt(n);
    // Sorting and count number of items:
    for (auto& it : item) std::cin >> it;
    std::sort(item.begin(), item.end());
    int pos = 0;
    for (int p = 0; p < n; ++p) {
        if (item[pos] != item[p]) {
            item[++pos] = item[p];
        }
        cnt[pos]++;
    }
    item.resize(pos+1);
    cnt.resize(pos+1);
    n = (int)item.size();
    // Calc prefix sums on count array:
    std::vector<int> sum(n+1);
    for (int i = 0; i < n; ++i) {
        sum[i+1] = sum[i] + cnt[i];
    }
    
    std::function<void(ll,int&,int&)> query = [&](ll id, int& fi, int& se) {
        for (int i = 0; i < n; ++i) {
            if ((ll)cnt[i] * sum[n] <= id) {
                id -= (ll)cnt[i] * sum[n];
                continue;
            }
            int low = 0, high = n+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if ((ll)cnt[i] * sum[mid] > id) {
                    high = mid;
                } else low = mid;
            }
            fi = item[i];
            se = item[low];
            return;
        }
    };
    
    int fi, se;
    query(need-1, fi, se);
    std::cout << fi << ' ' << se;
    return 0;
}
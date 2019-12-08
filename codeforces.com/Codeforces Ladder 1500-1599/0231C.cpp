/*
    Problem: 231C. To Add or Not to Add
    Solution: two pointers, sorting
*/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    
    std::sort(arr.begin(), arr.end());
    
    std::vector<int> diff(n);
    for (int i = 0; i < n; ++i) {
        diff[i] = arr.back() - arr[i];
    }
    int best_item = arr.back(), best_count = 1;
    int cur = n-1, sum = 0;
    for (int i = n-1; i > 0; --i) {
        while (cur-1 >= 0 && sum + diff[cur-1]-(arr.back()-arr[i]) <= k) {
            --cur;
            sum += diff[cur]-(arr.back()-arr[i]);
        }
        if (i - cur + 1 >= best_count) {
            best_count = i-cur+1;
            best_item = arr[i];
        }
        sum -= (i - cur) * (arr[i] - arr[i-1]);
    }
    std::cout << best_count << ' ' << best_item;
    
    return 0;
}
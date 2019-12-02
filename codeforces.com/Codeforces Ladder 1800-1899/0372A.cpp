/*
    Problem: 372A. Counting Kangaroos is Fun
    Solution: sorting, binary search, greedy, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using vi = std::vector<int>;
int main() {
    for (int n; std::cin >> n; ) {
        vi arr(n);
        for (auto &it : arr) std::cin >> it;
        std::sort(all(arr));
        int low = 0, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            int fi = 0, se = mid;
            while (fi < mid) {
                while (se < n && 2 * arr[fi] > arr[se]) se++;
                if (se == n) break;
                assert(2 * arr[fi] <= arr[se]);
                fi++,se++;
            }
            if (fi == mid) { low = mid; }
            else { high = mid; }
        }
        std::cout << n - low << std::endl;
    }
    return 0;
}
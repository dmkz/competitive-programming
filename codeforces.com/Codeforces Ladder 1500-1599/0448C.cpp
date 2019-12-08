/*
    Problem: 448C. Painting Fence
    Solution: recursion, dynamic programming, O(n^2)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#define io_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define       input(x) for (auto& it : (x)) std::cin >> it
#define         all(x) (x).begin(), (x).end()
#define make_unique(x) (x).erase(std::unique(all((x))), (x).end())

const int INF = (int)1e9+1;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;

int solve(int begin, int after, const vi& arr, vi& add) {
    int min = INF;
    for (int i = begin; i < after; ++i) {
        min = std::min(min, arr[i]-add[i]);
    }
    int answ = min;
    for (int i = begin; i < after; ++i) {
        add[i] += min;
    }
    for (int i = begin; i < after; ) {
        if (arr[i] == add[i]) { ++i;  continue; }
        int j = i;
        while (j < after && arr[j] != add[j]) ++j;
        answ += solve(i,j,arr,add);
        i = j;
    }
    return std::min(answ, after-begin);
}

int main() {
    io_fast;
    int n; std::cin >> n;
    vi arr(n), add(n);
    input(arr);
    std::cout << solve(0, n, arr, add);
    return 0;
}
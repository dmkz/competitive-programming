/*
    Problem: 460C. Present
    Solution: binary search, events, O(n log(MAX))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const int INF = (int)1e9+1;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;

bool solve(const vi& arr, int width, int min, int nOp) {
    vi add(size(arr)+width);
    int balance = 0;
    for (int i = 0; nOp >= 0 && i < size(arr); ++i) {
        int to_add = min - balance - arr[i];
        if (to_add > 0) {
            nOp -= to_add;
            balance += to_add;
            add[i+width-1] += to_add;
        }
        balance -= add[i];
    }
    return nOp >= 0;
}

int main() {
    ios_fast;
    int n, width, nOp;
    std::cin >> n >> nOp >> width;
    vi arr(n); input(arr);
    int low = *std::min_element(all(arr));
    int high = *std::max_element(all(arr))+nOp+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(arr,width,mid,nOp)) low = mid; else high = mid;
    }
    std::cout << low;
    return 0;
}
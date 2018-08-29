/*
    Problem: 817D. Imbalanced Array
    
    Solution: Sparse Table, binary search, dynamic programming, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#define all(x) (x).begin(), (x).end()
#define size(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Calculate array of log2:
    const int PMAX = 20, NMAX = 1024*1024;
    static int log2[1+NMAX];
    for (int i = 2; i <= NMAX; ++i) {
        log2[i] = log2[i/2]+1;
    }    
    
    // Input:
    int n; std::cin >> n;
    vi arr(n); for (auto& it : arr) std::cin >> it;
    
    // Calculate Sparse Table on min / max:
    static int min[PMAX][NMAX], max[PMAX][NMAX];
    
    for (int i = 0; i < n; ++i) {
        min[0][i] = max[0][i] = arr[i];
    }
    
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i + (1<<p)-1 < n; ++i) {
            min[p][i] = std::min(min[p-1][i], min[p-1][i+(1<<p-1)]);
            max[p][i] = std::max(max[p-1][i], max[p-1][i+(1<<p-1)]);
        }
    }
    
    // Function for min/max queries on segments:
    std::function<int(int,int)> get_min = [&](const int i, const int j) {
        const int len = j - i + 1;
        const int log = log2[len];
        return std::min(min[log][i], min[log][j-(1 << log)+1]);
    };
    
    std::function<int(int,int)> get_max = [&](const int i, const int j) {
        const int len = j - i + 1;
        const int log = log2[len];
        return std::max(max[log][i], max[log][j-(1 << log)+1]);
    };
    
    // smax[i] = sum of max values on segments [0,i],[1,i],[2,i],...,[i,i]
    // smin[i] = sum of min values on segments [0,i],[1,i],[2,i],...,[i,i]
    vll smax(n), smin(n);
    smin[0] = smax[0] = arr[0];
    
    // Calculate answer:
    ll answ = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i-1]) {
            smax[i] = smax[i-1] + arr[i];
            smin[i] = smin[i-1] + arr[i];
        } else if (arr[i] > arr[i-1]) {
            // Binary search on first element >= arr[i]
            int low = -1, high = i-1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (get_max(mid,i-1) < arr[i]) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            // Update smin and smax:
            if (low != -1) {
                smax[i] += smax[low];
            }
            smax[i] += 1LL * (i - low) * arr[i];
            smin[i] = smin[i-1] + arr[i];
        } else {
            // Binary search on first element <= arr[i]
            int low = -1, high = i-1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (get_min(mid,i-1) > arr[i]) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            // Update smin and smax:
            if (low != -1) {
                smin[i] += smin[low];
            }
            smin[i] += 1LL * (i - low) * arr[i];
            smax[i] = smax[i-1] + arr[i];
        }
        // Update answer:
        answ += smax[i] - smin[i];
    }
    // Output:
    std::cout << answ;
    return 0;
}
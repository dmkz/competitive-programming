/*
    Problem: 463C. Gargari and Bishops
    Solution: brute force, greedy, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<ll> diag1(2*n); // r + c
    std::vector<ll> diag2(2*n); // n + r - c
    
    std::vector<std::vector<int>> arr(n, std::vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            std::cin >> arr[r][c];
            diag1[r+c] += arr[r][c];
            diag2[n+r-c] += arr[r][c];
        }
    }
    
    ll mxSum1 = -1, mxSum2 = -1, mxRow1=0, mxCol1=0, mxRow2=0, mxCol2=0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            auto sum = diag1[r+c] + diag2[n+r-c] - arr[r][c];
            if ((r+c)%2 == 0) {
                if (mxSum1 < sum) {
                    mxSum1 = sum;
                    mxRow1 = r+1;
                    mxCol1 = c+1;
                }
            } else {
                if (mxSum2 < sum) {
                    mxSum2 = sum;
                    mxRow2 = r+1;
                    mxCol2 = c+1;
                }
            }
        }
    }
    assert(mxRow1 > 0 && mxCol1 > 0 && mxRow2 > 0 && mxCol2 > 0);
    std::cout << mxSum1 + mxSum2 << '\n';
    std::cout << mxRow1 << ' ' << mxCol1 << ' ' << mxRow2 << ' ' << mxCol2;
    return 0;
}
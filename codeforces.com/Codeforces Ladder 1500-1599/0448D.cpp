/*
    Problem: 448D. Multiplication Table
    Solution: binary search
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

ll solve(ll nRows, ll nCols, ll need) {
    ll low = 0, high = nRows * nCols+1;
    while (high - low > 1) {
        ll mid = (low+high)/2;
        ll count = 0;
        for (ll r = 1; r <= nRows; ++r) {
            // r, 2*r, 3*r, 4*r, 5*r, ..., k * r
            //k * r < mid;
            ll k = mid / r;
            while (k >= 1 && k * r >= mid) --k;
            while (k+1<=nCols && (k+1)*r < mid) ++k;
            k = std::min(k, nCols);
            count += k;
            
        }
        if (count >= need) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return low;
}

int main() {
    int nRows, nCols; ll need;
    std::cin >> nRows >> nCols >> need;
    std::cout << solve(nRows, nCols, need);
    
    return 0;
}
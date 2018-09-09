/*
    Problem: 762D. Maximum path

    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <functional>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<std::vector<ll>> arr(3, std::vector<ll>(n));
    for (auto & row : arr) {
        for (auto & it : row) {
            std::cin >> it;
        }
    }
    
    const ll INF = (ll)1e18L;
    std::vector<std::vector<ll>> max(3, std::vector<ll>(n+1, -INF));
    max[2].back() = 0;
    std::function<ll(int,int)> get_max = [&](const int row, const int col) {
        if (max[row][col] == -INF) {
            ll& value = max[row][col];
            if (col == n-1) {
                value = 0;
                for (int r = row; r < 3; ++r) {
                    value += arr[r][n-1];
                }
            } else if (col < n) {
                if (row == 0) {
                    value = std::max(value, arr[0][col] + get_max(0,col+1));
                    value = std::max(value, arr[0][col] + arr[1][col] + get_max(1,col+1));
                    value = std::max(value, arr[0][col] + arr[1][col] + arr[2][col] + get_max(2,col+1));
                    value = std::max(value, 
                        arr[0][col] + arr[0][col+1] + 
                        arr[1][col+1] + arr[1][col] + 
                        arr[2][col] + arr[2][col+1] + get_max(2, col+2)
                    );
                } else if (row == 1) {
                    value = std::max(value, arr[1][col] + get_max(1,col+1));
                    value = std::max(value, arr[1][col] + arr[0][col] + get_max(0, col+1));
                    value = std::max(value, arr[1][col] + arr[2][col] + get_max(2, col+1));
                } else {
                    value = std::max(value, arr[2][col] + get_max(2,col+1));
                    value = std::max(value, arr[2][col] + arr[1][col] + get_max(1,col+1));
                    value = std::max(value, arr[2][col] + arr[1][col] + arr[0][col] + get_max(0, col+1));
                    value = std::max(value, 
                        arr[2][col] + arr[2][col+1] + 
                        arr[1][col+1] + arr[1][col] + 
                        arr[0][col] + arr[0][col+1] + get_max(0, col+2)
                    );
                }
            }
        }
        //assert(max[row][col] != -INF);
        return max[row][col];
    };
    std::cout << get_max(0,0);
    
    return 0;
}
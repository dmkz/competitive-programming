/*
    Problem: 467C. George and Job
    Solution: dynamic programming
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    int n, len, count;
    std::cin >> n >> len >> count;

    std::vector<ll> sum{0};
    for (int i = 1; i <= n; ++i) {
        int value; std::cin >> value;
        sum.push_back(sum.back() + value);
    }
    
    std::vector<ll> fix(n-len+1);
    for (int i = 0; i+len-1 < n; ++i) {
        fix[i] = sum[i+len] - sum[i];
    }
    
    std::vector<std::vector<ll>> max(1+count, std::vector<ll>(n+1,0));
    for (int cnt = 1; cnt <= count; ++cnt) {
        for (int pos = (int)fix.size()-1; pos >= 0; --pos) {
            max[cnt][pos] = std::max(max[cnt][pos+1], fix[pos] + max[cnt-1][pos+len]);
        }
    }
    std::cout << max[count][0];

    return 0;
}
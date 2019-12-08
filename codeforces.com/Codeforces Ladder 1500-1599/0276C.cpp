/*
    Problem: 276C. Little Girl and Maximum Sum
    Solution: greedy, sorting
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> cand(n);
    for (auto& it : cand) std::cin >> it;
    std::sort(cand.begin(), cand.end());
    
    std::vector<int> inc(n), dec(n);
    while (q--) {
        int l, r; std::cin >> l >> r; --l, --r;
        inc[l]++; dec[r]++;
    }
    
    std::vector<int> coeff;
    int balance = 0;
    for (int i = 0; i < n; ++i) {
        balance += inc[i];
        coeff.push_back(balance);
        balance -= dec[i];
    }
    std::sort(coeff.begin(), coeff.end());
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += (ll)coeff[i] * cand[i];
    }
    std::cout << sum;
    
    return 0;
}
/*
    "Антиарифметическая перестановка": разделяй и властвуй, O(n*log(n))
*/

#include <iostream>
#include <vector>

void solve(std::vector<int>& answ, int l, int r) {
    if (r == l) {
        return;
    }
    {
        std::vector<int> first;
        for (int i = l; i <= r; i += 2) {
            first.push_back(answ[i]);
        }
        std::vector<int> second;
        for (int i = l+1; i <= r; i += 2) {
            second.push_back(answ[i]);
        }
        int p = l;
        for (auto& it : first) {
            answ[p++] = it;
        }
        for (auto& it : second) {
            answ[p++] = it;
        }
    }
    solve(answ,   l, (l+r)/2);
    solve(answ, (l+r)/2+1, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> answ(n);
    for (int i = 0; i < n; ++i) answ[i] = i;
    solve(answ, 0, n-1);
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}
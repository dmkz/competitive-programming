// problem: 818E
#include <bits/stdc++.h>
#include "../SparseTable.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    int n, k; std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] %= k;
    }
    SparseTable<int, MultByModulo, 1> st(a, MultByModulo(k));
    int64_t answ{};
    for (int L = 0; L < n; L++) {
        int R = st.binary_lifting(L, extendIfNonZero);
        answ += n - R;
    }
    std::cout << answ << std::endl;
}
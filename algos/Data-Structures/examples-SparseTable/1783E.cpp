#include "template.hpp"
#include "debug.hpp"
#include "sparsetable.hpp"
int main() {
    int tt; std::cin >> tt;
    while (tt--) {
        int n; std::cin >> n;
        vi a(n), b(n);
        std::cin >> a >> b;
        vi minB(1+n, n+1);
        for (int i = 0; i < n; i++)
            std::remin(minB[a[i]], b[i]);
        using namespace algos::SparseTable;
        SparseTable<int, Min<int>> st(minB);
        vi answ;
        for (int k = 1; k <= n; k++) {
            bool ok = 1;
            for (int t = 1; k * t + 1 <= n; t++)
                if (st(t*k+1,n) <= t * k)
                    ok = false;
            if (ok) answ << k;
        }
        std::cout << isz(answ) << '\n';
        for (auto it : answ) std::cout << it << ' ';
        std::cout << '\n';
    }
}

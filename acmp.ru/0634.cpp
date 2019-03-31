/*
    Задача: 634. Кубок CBOSS
    
    Решение: перестановки, перебор, O(n!*k)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, k; std::cin >> n >> k; ) {
        vvi a(n, vi(n,0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> a[i][j];
            }
        }
        vi t(n);
        for (auto &it : t) { std::cin >> it; }
        vi perm(n), answ;
        for (int i = 0; i < n; ++i) { perm[i] = i; }
        int best = (int)1e9+7;
        do {
            int curr = 0;
            for (int i = 0; i < k; ++i) {
                int v = perm[i];
                if (i > 0) {
                    int u = perm[i-1];
                    curr += a[u][v];
                }
                curr += t[v];
            }
            if (curr < best) {
                best = curr;
                answ.assign(perm.begin(), perm.begin()+k);
            }
        } while (std::next_permutation(all(perm)));
        std::cout << best << '\n';
        for (auto &it : answ) { std::cout << it+1 << ' '; }
        std::cout << std::endl;
    }
    return 0;
}
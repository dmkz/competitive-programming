/*
    Задача: 565. Сушка
    
    Решение: жадный алгоритм, сортировка, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
struct Pair {
    int w, d, id;
};
bool operator<(const Pair& a, const Pair& b) {
    return a.d < b.d || (a.d == b.d && (a.w > b.w || (a.w == b.w && a.id < b.id)));
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, r, t = 0; std::cin >> n >> r;) {
        std::vector<Pair> arr(n);
        typedef std::pair<int,int> pii;
        std::vector<pii> answ;
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i].w >> arr[i].d;
            arr[i].id = i+1;
        }
        std::sort(all(arr));
        if (r == 1) {
            bool ok = true;
            for (auto it : arr) {
                ok = ok && (it.d >= it.w);
            }
            if (!ok) {
                std::cout << "Impossible" << std::endl;
            }
            continue;
        }
        bool ok = true;
        for (auto it : arr) {
            // w - (d - k) - k * r <= 0
            // w - d + k - k * r <= 0
            // w - d + k * (1 - r) <= 0
            const int d = it.d;
            const int w = it.w;
            int k = (d - w) / (1-r);
            while (w - d - k * (r - 1) > 0) { ++k; }
            while (w - d - (r - 1) * (k-1) <= 0) { --k; }
            assert(w - d + k * (1 - r) <= 0);
            if (t + k > d) {
                ok = false;
                break;
            }
            if (k > 0) {
                answ.push_back(pii(t, it.id));
                t += k;
            }
        }
        if (!ok) {
            std::cout << "Impossible" << std::endl;
            continue;
        }
        for (auto it : answ) { 
            std::cout << it.first << ' ' << it.second << '\n';
        }
    }
    return 0;
}
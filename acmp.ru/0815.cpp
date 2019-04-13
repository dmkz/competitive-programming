/*
    Задача: 815. Обходчик лабиринтов
    
    Решение: графы, поиск в ширину, динамическое программирование, O(L * (N + M))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n, nE, k;
    while (std::cin >> n >> nE >> k) {
        vi begin(nE), end(nE), color(nE);
        for (int i = 0; i < nE; ++i) {
            std::cin >> begin[i] >> end[i] >> color[i];
        }
        int nOp; std::cin >> nOp;
        vi op(nOp);
        for (auto &it : op) { std::cin >> it; }
        int s; std::cin >> s;
        vi curr(1+n), next(1+n);
        curr[s] = 1;
        bool ok = true;
        for (auto c : op) {
            bool was = false;
            for (int i = 0; i < nE; ++i) {
                if (color[i] == c && curr[begin[i]]) {
                    next[end[i]] = 1;
                    was = true;
                }
            }
            if (!was) {
                ok = false;
                break;
            }
            curr = next;
            std::fill(all(next), 0);
        }
        if (!ok) { std::cout << "Hangs\n"; continue; }
        vi answ; 
        for (int i = 1; i <= n; ++i) {
            if (curr[i]) { answ.push_back(i); }
        }
        std::cout << "OK\n";
        std::cout << isz(answ) << "\n";
        for (auto it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}
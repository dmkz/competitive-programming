/*
    Задача: 874. Гирлянда
    
    Решение: перебор, битмаски, O((n+m)*k^n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

struct Edge { int u, v; };

template<const int nC> 
int solve(const int nV, const std::vector<Edge>& edges) {
    int answ = 0; const int limit = (int)std::pow(nC, nV);
    std::vector<int> color(nV);
    for (int mask = 0; mask < limit; ++mask) {
        for (int temp = mask, i = 0; i < nV; ++i) {
            color[i] = temp % nC;
            temp /= nC;
        }
        bool ok = true;
        for (auto &e : edges) {
            if (color[e.u] == color[e.v]) {
                ok = false;
                break;
            }
        }
        answ += ok;
    }
    return answ;
}

int main() {
    int nV, nC, nE;
    while (std::cin >> nV >> nC >> nE) {
        std::vector<Edge> edges(nE);
        for (auto &e : edges) { std::cin >> e.u >> e.v; e.u--, e.v--; }
        int answ = 0;
        switch(nC) {
            case 1: answ = solve<1>(nV, edges); break;
            case 2: answ = solve<2>(nV, edges); break;
            case 3: answ = solve<3>(nV, edges); break;
            case 4: answ = solve<4>(nV, edges); break;
            case 5: answ = solve<5>(nV, edges); break;
            case 6: answ = solve<6>(nV, edges); break;
            case 7: answ = solve<7>(nV, edges); break;
            case 8: answ = solve<8>(nV, edges); break;
        };
        std::cout << answ << std::endl;
    }
    return 0;
}
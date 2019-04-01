/*
    Задача: 703. ACM-шахматы
    
    Решение: поиск в ширину, графы, строки, O(n*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::string fi, se, tmp;
    while (std::cin >> fi >> se) {
        for (int i = 0; i < 2; ++i) {
            std::cin >> tmp; fi += tmp;
            std::cin >> tmp; se += tmp;
        }
        std::map<std::string, int> dist;
        dist[fi] = 0;
        std::queue<std::string> queue;
        queue.push(fi);
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            int currDist = dist[curr];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (curr[3*i+j] == 'W' || curr[3*i+j] == 'B') {
                        for (int di = -2; di <= 2; ++di) {
                            for (int dj = -2; dj <= 2; ++dj) {
                                if (di * di + dj * dj != 5) { continue; }
                                const int ni = i + di, nj = j + dj;
                                if (ni < 0 || nj < 0 || ni >= 3 || nj >= 3) { continue; }
                                if (curr[3*ni+nj] != '.') { continue; }
                                std::swap(curr[3*i+j], curr[3*ni+nj]);
                                auto it = dist.find(curr);
                                if (it == dist.end()) {
                                    dist[curr] = currDist+1;
                                    queue.push(curr);
                                } else {
                                    assert(it->second <= currDist+1);
                                }
                                std::swap(curr[3*i+j], curr[3*ni+nj]);
                            }
                        }
                    }
                }
            }
        }
        auto it = dist.find(se);
        int answ = (it == dist.end() ? -1 : it->second);
        std::cout << answ << '\n';
    }
    return 0;
}
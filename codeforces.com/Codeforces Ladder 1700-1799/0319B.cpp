/*
    Problem: 319B. Psychos in a Line
    
    Solution: data structures, modeling, implementation, O(n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

const int INF = (int)1e9+7;

typedef std::vector<int> vi;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; std::cout << std::endl) {
        vi next(1+n, INF), prev(1+n, -INF);
        int prev_ = -1;
        for (int i = 0; i < n; ++i) {
            int curr; std::cin >> curr;
            if (prev_ != -1) {
                next[prev_] = curr;
                prev[curr] = prev_;
            }
            prev_ = curr;
        }
        std::set<int> can_kill;
        vi killed;
        for (int i = 1; i <= n; ++i) {
            if (i > next[i]) {
                can_kill.insert(i);
            }
        }
        int answ = 0;
        while (!can_kill.empty()) {
            for (auto it = can_kill.begin(); it != can_kill.end(); ) {
                auto next_ = std::next(it);
                if (*it > next[*it]) {
                    killed.push_back(next[*it]);
                } else {
                    can_kill.erase(it);
                }
                it = next_;
            }
            if (killed.empty()) {
                break;
            }
            answ++;
            while (!killed.empty()) {
                auto back = killed.back(); killed.pop_back();
                auto it = can_kill.find(back);
                if (it != can_kill.end()) {
                    can_kill.erase(it);
                }
                const int pv = prev[back];
                const int nx = next[back];
                assert(!(pv == -INF && nx == INF));
                if (nx == INF) {
                    next[pv] = nx;
                } else if (pv == -INF) {
                    prev[nx] = pv;
                } else {
                    next[pv] = nx;
                    prev[nx] = pv;
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}
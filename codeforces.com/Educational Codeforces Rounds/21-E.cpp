/*
    Problem: 808E. Selling Souvenirs
    
    Solution: dynamic programming, greedy, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

typedef long long ll;

struct State {
    ll cost; int n1, n2;
    
    inline State add(int type, int cost_) const {
        return type == 1 ? State{cost+cost_, n1+1, n2} : State{cost+cost_, n1, n2+1};
    }
};

inline bool operator<(const State& a, const State& b) {
    return a.cost < b.cost || (a.cost == b.cost && (a.n2 > b.n2 || (a.n2 == b.n2 && a.n1 > b.n1)));
}

inline bool operator>(const State& a, const State& b) {
    return b < a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, wmax; std::cin >> n >> wmax;
    std::vector<int> cost[4];
    for (int i = 0; i < n; ++i) {
        int w, c; std::cin >> w >> c;
        cost[w].push_back(c);
    }
    for (int i = 1; i <= 3; ++i) {
        std::sort(cost[i].begin(), cost[i].end(), std::greater<int>());
    }
    std::vector<State> max(1+wmax, State{0,0,0});
    for (int w = 0; w < wmax; ++w) {
        auto curr = max[w];
        max[w+1] = std::max(max[w+1], curr);
        if (w + 1 <= wmax && curr.n1 < (int)cost[1].size()) {
            max[w+1] = std::max(max[w+1], curr.add(1, cost[1][curr.n1]));
        }
        if (w + 2 <= wmax && curr.n2 < (int)cost[2].size()) {
            max[w+2] = std::max(max[w+2], curr.add(2, cost[2][curr.n2]));
        }
    }
    std::vector<ll> pref{0};
    for (auto it : cost[3]) {
        pref.push_back(pref.back() + it);
    }
    ll answ = 0;
    for (int n3 = 0; wmax - n3*3 >= 0 && n3 <= (int)cost[3].size(); ++n3) {
        answ = std::max(max[wmax-n3*3].cost+pref[n3], answ);
    }
    std::cout << answ;
    return 0;
}
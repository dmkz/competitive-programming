/*
    Problem: 339C. Xenia and Weights
    Solution: bfs, graphs, dynamic programming, O(m * d^2)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <queue>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const int mod = (int)1e9+7;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

struct State {

    int value;
    
    State(int step, int diff, int last) : value(last + ((diff+10) << 4) + (step << 9)) { }
    State(int value_ = 0) : value(value_) { }
    inline int step() const { return value >> 9; }
    inline int diff() const { return ((value >> 4) & 31) - 10; }
    inline int last() const { return value & 15; }
    operator int() { return value; }
};

int main() {
    ios_fast;
    std::string can; std::cin >> can; can = "1" + can;
    for (auto& it : can) it = char(it - '0');
    
    int nSteps; std::cin >> nSteps;
    // state: [step][diff][last] = 1024 * 32 * 16
    std::queue<State> queue;
    queue.push(State(0,0,0));
    std::vector<int> from(1024*32*16, -1);
    from[State(0,0,0)] = State(0,0,0);
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        if (curr.step() == nSteps) continue;
        if (curr.diff() <= 0) {
            for (int d = 1; d <= 10; ++d) {
                if (d == curr.last() || !can[d]) continue;
                if (curr.diff() + d > 0) {
                    auto next = State(curr.step() + 1, curr.diff() + d, d);
                    if (from[next] == -1) {
                        from[next] = curr;
                        queue.push(next);
                    }
                }
            }
        } else {
            for (int d = 1; d <= 10; ++d) {
                if (d == curr.last() || !can[d]) continue;
                if (curr.diff() - d < 0) {
                    auto next = State(curr.step() + 1, curr.diff() - d, d);
                    if (from[next] == -1) {
                        from[next] = curr;
                        queue.push(next);
                    }
                }
            }
        }
    }
    State curr(0); bool flag = false;
    for (int diff = -10; diff <= 10; ++diff) {
        for (int last = 1; last <= 10; ++last) {
            if (!can[last]) continue;
            if (from[State(nSteps,diff,last)] != -1) {
                curr = State(nSteps, diff, last);
                flag = true;
                break;
            }
        }
    }
    if (!flag) {
        std::cout << "NO"; return 0;
    }
    vi answ;
    while (curr != from[curr]) {
        answ.push_back(curr.last());
        curr = from[curr];
    }
    std::cout << "YES\n";
    std::reverse(all(answ));
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}
#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

struct State {
    int heads, tails;
};

int solve(int nHeads, int nTails) {
//  bfs from position {0, 0}
    std::vector<std::vector<int>> min(1024, std::vector<int>(1024, -1));
    min[0][0] = 0;
    std::queue<State> queue;
    queue.push(State{0, 0});
    
    std::function<bool(const State&)> correct = [&](const State& s){
        return 0 <= s.heads && s.heads < 1024 && 0 <= s.tails && s.tails < 1024;
    };
    
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        // cut two heads:
        { auto prev = curr; prev.heads += 2;
            if (correct(prev) && min[prev.heads][prev.tails] == -1) {
                min[prev.heads][prev.tails] = min[curr.heads][curr.tails]+1;
                queue.push(prev);
            }
        }
        // cut two tails:
        if (curr.heads >= 1) { 
            auto prev = curr; prev.heads -= 1; prev.tails += 2;
            if (correct(prev) && min[prev.heads][prev.tails] == -1) {
                min[prev.heads][prev.tails] = min[curr.heads][curr.tails]+1;
                queue.push(prev);
            }
        }
        // cut one tail: 
        if (curr.tails >= 2) {
            auto prev = curr; prev.tails -= 1;
            if (correct(prev) && min[prev.heads][prev.tails] == -1) {
                min[prev.heads][prev.tails] = min[curr.heads][curr.tails]+1;
                queue.push(prev);
            }
        }
    }
    return min[nHeads][nTails];
}

int main() {
    int nHeads, nTails; 
    scanf("%d %d", &nHeads, &nTails);
    printf("%d\n", solve(nHeads, nTails));
    return 0;
}
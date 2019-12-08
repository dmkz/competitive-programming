/*
    Problem: 508C. Anya and Ghosts
    Solution: constructive, greedy, binary search
*/
#include <iostream>
#include <algorithm>
#include <vector>

bool can(int have, int time, int need, const std::vector<int>& pos) {
    int mx = pos.back();
    std::vector<bool> used(1+mx, false);
    std::vector<int> count(1+mx, 0);
    for (auto p : pos) {
        int diff = need - count[p];
        int curr = p-1;
        while (diff && have) {
            while (p - curr <= time && used[curr]) --curr;
            if (p-curr > time) return false;
            --have,--diff;
            used[curr] = true;
            for (int i = curr+1; i <= std::min(mx,curr + time); ++i) {
                count[i]++;
            }
        }
        if (diff != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int nGhosts, time, need;
    std::cin >> nGhosts >> time >> need;
    
    std::vector<int> pos;
    
    for (int i = 0; i < nGhosts; ++i) {
        int p; std::cin >> p;
        pos.push_back(300+p);
    }
    
    int low = 0, high = 601;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(mid,time,need,pos)) { 
            high = mid; 
        } else {
            low = mid; 
        }
    }
    int answ = low + 1;
    if (!can(answ,time,need,pos))answ = -1;
    std::cout << answ;
    return 0;
}
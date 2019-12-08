/*
    Problem: 505C. Mr. Kitayuta, the Treasure Hunter
    Solution: hash table, dynamic programming
*/
#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
//gp_hash_table<int, int> table; -- example

int main() {
    int n, d; std::cin >> n >> d;
    
    std::vector<int> inc(1+30000);
    for (int i = 0; i < n; ++i) {
        int v; std::cin >> v;
        inc[v]++;
    }
    std::vector<int> suff(1+30000+1);
    for (int i = 30000; i >= 0; --i) {
        suff[i] = suff[i+1] + inc[i];
    }
    
    std::vector<gp_hash_table<int, int>> event(1+30000);
    event[d][d] = 0;
    
    int answ = 0;
    for (int i = 0; i <= 30000; ++i) {
        for (auto& it : event[i]) {
            int jump = it.first;
            int count = it.second + inc[i];
            answ = std::max(count, answ);
            if (jump <= 2) {
                answ = std::max(count + suff[i+1], answ);
            } else {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (i+jump+dj > 30000) {
                        continue;
                    }
                    if (i+jump+dj+jump+dj-1 > 30000) {
                        answ = std::max(count + inc[i+jump+dj], answ);
                        continue;
                    }
                    event[i+jump+dj][jump+dj] = std::max(event[i+jump+dj][jump+dj], count);
                }
            }
        }
        event[i].clear();
    }
    std::cout << answ;
    return 0;
}
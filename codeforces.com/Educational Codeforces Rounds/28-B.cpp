/*
    Problem: 846B. Math Show
    
    Solution: dynamic programming, O(n^2*k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;
const ll INF = (ll)1e18L;
int main() {
    int nProblems, nSubtask, limit;
    scanf("%d %d %d", &nProblems, &nSubtask, &limit);
    vl time(1+nSubtask);
    for (int i = 1; i <= nSubtask; ++i) {
        int t; scanf("%d", &t);
        time[i] = t;
    }
    std::sort(time.begin(), time.end());
    for (int i = 1; i <= nSubtask; ++i) {
        time[i] += time[i-1];
    }
    const int MAX = (nSubtask+1)*nProblems;
    vvl minTime(1+nProblems, vl(MAX+1, INF));
    minTime[0][0] = 0;
    for (int p = 1; p <= nProblems; ++p) {
        for (int currRes = 0; currRes <= MAX; ++currRes) {
            for (int currSubtask = 0; currSubtask <= nSubtask; ++currSubtask) {
                int prevRes = currRes - ((currSubtask == nSubtask) + currSubtask);
                if (prevRes < 0) continue;
                minTime[p][currRes] = std::min(minTime[p-1][prevRes] + time[currSubtask], minTime[p][currRes]);
            }
        }
    }
    int max = 0;
    for (int curr = 0; curr <= MAX; ++curr) {
        if (minTime[nProblems][curr] <= limit) {
            max = std::max(max, curr);
        }
    }
    printf("%d", max);
    return 0;
}
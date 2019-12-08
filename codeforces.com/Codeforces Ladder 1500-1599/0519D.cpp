/*
    Problem: 519D. A and B and Interesting Substrings
    Solution: std::map, dynamic programming, O(n log(n))
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <numeric>

typedef long long ll;

int main() {
    // Input:
    std::vector<int> cost(256);
    for (char c = 'a'; c <= 'z'; ++c) {
        int value; std::cin >> value;
        cost[c] = value;
    }
    std::string s;
    std::cin >> s;
    
    // Prepare array of positions for chars and prefix sums:
    std::vector<std::vector<int>> pos(26);

    std::vector<ll> sum{0};
    
    for (int i = 0; i < (int)s.size(); ++i) {
        pos[s[i]-'a'].push_back(i);
        sum.push_back(sum.back() + cost[s[i]]);
    }
    
    // Calculate answer:
    ll answ = 0;
    for (auto& p : pos) {
        // Prepare map for answer to queries in O(log(n)) time:
        std::map<ll,int> count;
        for (int i = 1; i < (int)p.size(); ++i) {
            ll curr = (p[i]-1 == p[0] ? 0 : sum[p[i]]-sum[p[0]+1]);
            count[curr]++;
        }
        // Calculate answer for current char:
        ll search = 0;
        for (int i = 1; i < (int)p.size(); ++i) {
            answ += count[search];
            ll to_erase = search + (sum[p[i]]-sum[p[i-1]+1]);
            count[to_erase]--;
            search += (sum[p[i]+1]-sum[p[i-1]+1]);
        }
    }
    std::cout << answ << std::endl;
    
    return 0;
}
/*
    Problem: B. Poker
    Solution: strings, counting, implementation, O(n)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int t; std::cin >> t;
    while (t--) {
        std::string s;
        std::map<std::string, int> cnt;
        for (int i = 0; i < 5; i++) {
            std::cin >> s;
            cnt[s]++;
        }
        vi mask;
        for (auto& it : cnt) {
            mask.push_back(it.second);
        }
        std::sort(all(mask));
        if (mask == vi{1,1,1,1,1}) { std::cout << "no pair\n"; }
        else if (mask == vi{1,1,1,2}) { std::cout << "pair\n"; }
        else if (mask == vi{1,2,2}) { std::cout << "two pair\n"; }
        else if (mask == vi{1,1,3}) { std::cout << "set\n"; }
        else if (mask == vi{2,3}) { std::cout << "full house\n"; }
        else if (mask == vi{1,4}) { std::cout << "quads\n"; }
        else { assert(mask == vi{5}); std::cout << "poker\n"; }
    }
    return 0;
}
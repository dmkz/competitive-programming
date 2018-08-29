/*
    Problem: 818D. Multicolored Cars
    
    Solution: implementation, set, constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <set>

struct Pair {
    int color, count;
};

inline bool operator<(const Pair& a, const Pair& b) {
    return a.count < b.count || (a.count == b.count && a.color < b.color);
}

const int MAX = (int)1e6;

int main() {
    // Input and prepare candidates for answer:
    int n, color1;
    scanf("%d %d", &n, &color1);
    std::set<Pair> set;
    set.insert(Pair{color1,0});
    std::vector<int> input(n), cnt(1+MAX), can(1+MAX, true);
    for (auto& it : input) {
        scanf("%d", &it);
        set.insert(Pair{it,0});
    }
    // Erase all colors which count is less on i-th moment than color1:
    for (auto c : input) {
        if (!can[c]) continue;
        set.erase(Pair{c, cnt[c]++});
        set.insert(Pair{c, cnt[c]});
        while (set.begin()->count < cnt[color1]) {
            can[set.begin()->color] = false;
            set.erase(set.begin());
        }
    }
    // Output:
    if ((int)set.size() > 1) {
        set.erase(Pair{color1, cnt[color1]});
        printf("%d", set.begin()->color);
    } else {
        printf("-1");
    }
    return 0;
}
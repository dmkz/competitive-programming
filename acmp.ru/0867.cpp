/*
    "Экзамен - 2": сортировка, два указателя, O(n log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>

struct Pair {
    int pos, id;
};

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);
    
    std::vector<Pair> pairs;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        pairs.push_back(Pair{x, i});
    }
    
    std::sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) {
        return a.pos < b.pos;
    });
    
    std::set<int> curr;
    for (int i = 1; i <= n; ++i) {
        curr.insert(i);
    }
    
    std::vector<int> answ(n);
    
    int l = 0, r = -1;
    while (l < n) {
        while (r+1 < n && pairs[r+1].pos - pairs[l].pos <= dist) {
            ++r;
            answ[pairs[r].id] = *curr.begin();
            curr.erase(curr.begin());
        }
        curr.insert(answ[pairs[l].id]);
        ++l;
    }
    
    printf("%d\n", *std::max_element(answ.begin(), answ.end()));
    
    for (auto& it : answ) {
        printf("%d ", it);
    }
    
    return 0;
}
#include <bits/stdc++.h>
const int NMAX = 500*1000+5;
void combine(std::list<int>*& dst, std::list<int>*& src) {
    if (dst == src) return;
    // we will add positions from smaller list to larger
    // in each "union" operation
    std::list<int> *small = src, *large = dst;
    if (dst->size() < src->size()) {
        std::swap(small,large);
    }
    large->insert(large->end(), small->begin(), small->end());
    small->clear();
    dst = large;
    src = small;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int q; std::cin >> q;
    // we will store positions of each symbol in the list
    std::vector<std::list<int>*> list(NMAX);
    for (int i = 0; i < NMAX; i++) {
        list[i] = new std::list<int>{};
    }
    // process all queries:
    int n = 0;
    while (q --> 0) {
        int t, x; std::cin >> t >> x;
        if (t == 1) list[x]->push_back(n++);
        else {
            int y; std::cin >> y;
            combine(list[y], list[x]);
        }
    }
    // build answer, using lists of positions of each item:
    std::vector<int> answ(n);
    for (int i = 0; i < NMAX; i++) {
        for (auto pos : *list[i]) answ[pos] = i;
    }
    for (auto it : answ) std::cout << it << ' ';
    std::cout << '\n';
    return 0;
}
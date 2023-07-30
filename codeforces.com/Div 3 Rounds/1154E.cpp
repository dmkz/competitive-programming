/*
    problem: 1154E. Two Teams
    solution: std::set, positions of items, find, erase, segment of std::set, iterators
*/
#include "template.hpp"
int main() {
    int n, k; std::cin >> n >> k;
    std::set<pii> sortedByPos, sortedByItem;
    auto add = [&](int i, int x) {
        sortedByPos << pii(i,x);
        sortedByItem << pii(x,i);
    };
    for (int i = 0, x; i < n; i++) {
        std::cin >> x;
        add(i, x);
    }
    vi answer(n);
    auto take = [&](int id) {
        // найти позицию максимума
        assert(isz(sortedByItem));
        auto [xmax, imax] = sortedByItem--;
        auto middle = sortedByPos.find({imax,xmax});
        answer[imax] = id;
        // k человек справа
        int taken = 0;
        for (auto it = std::next(middle); it != sortedByPos.end() && taken < k; taken++)
        {
            answer[it->first] = id;
            sortedByItem.erase({it->second, it->first});
            it = sortedByPos.erase(it);
        }
        if (auto it = middle; it != sortedByPos.begin())
        {
            taken = 0;
            it = std::prev(it);
            while (true) {
                answer[it->first] = id;
                taken++;
                if (it == sortedByPos.begin()) {
                    sortedByItem.erase(pii(it->second, it->first));
                    sortedByPos.erase(it);
                    break;
                }
                auto prev = std::prev(it);
                sortedByItem.erase(pii(it->second, it->first));
                sortedByPos.erase(it);
                it = prev;
                if (taken == k)
                    break;
            }
        }
        sortedByPos.erase(middle);
    };
    int id = 2;
    while (isz(sortedByItem)) {
        id = 1 + 2 - id;
        take(id);
    }
    for (auto it : answer) std::cout << it;
    std::cout << std::endl;
    return 0;
}

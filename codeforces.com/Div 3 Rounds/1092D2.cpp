/*
    problem: 1092D2. Great Vova Wall (Version 2)
    solution: set of segments, std::set, implementation, O(n log(n))
*/
#include "template.hpp"
std::string solve(int n, vi a) {
    std::set<tiii> segsVal, segsPos;
    auto insert = [&](int i, int j, int val) {
        segsVal << tiii{val, i, j};
        segsPos << tiii{i, j, val};
    };
    auto erase = [&](int i, int j, int val) {
        // удалить из множества посорченного по значению
        auto itVal =  segsVal.find(tiii(val,i,j));
        assert(itVal != segsVal.end());
        segsVal.erase(itVal);
        // удалить из множества посорченного по бегину
        auto itPos = segsPos.find(tiii(i,j,val));
        assert(itPos != segsPos.end());
        segsPos.erase(itPos);
    };
    for (int i = 0, j; i < n; i = j) {
        for (j = i; j < n && a[i] == a[j]; j++);
        insert(i,j,a[i]);
    }
    while (isz(segsVal) > 1) {
        // вынимаем минимум
        auto [val, i, j] = *segsVal.begin();
        watch("curr",i,j,val);
        if ((j - i) % 2 == 1)
            return "NO";
        // надо найти соседей
        auto it = segsPos.find(tiii(i,j,val));
        assert(it != segsPos.end());
        int leftVal = INT_MIN, leftI, leftJ;
        if (it != segsPos.begin()) // есть сосед слева
            std::tie(leftI,leftJ,leftVal) = *std::prev(it);
        int rightVal = INT_MIN, rightI, rightJ;
        if (std::next(it) != segsPos.end()) // есть сосед справа
            std::tie(rightI,rightJ,rightVal) = *std::next(it);
        // удалить текущий отрезок
        erase(i,j,val);
        // увеличить значение до минимума соседей
        val = std::max(leftVal, rightVal);
        // объединить с левым соседом
        if (val == leftVal) { // удалить соседа слева
            erase(leftI, leftJ, leftVal);
            i = leftI;
        }
        // объединить с правым соседом
        if (val == rightVal) {
            erase(rightI, rightJ, rightVal);
            j = rightJ;
        }
        insert(i,j,val);
    }
    return "YES";
}

int32_t main() {
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    std::cout << solve(n,a) << std::endl;
    return 0;
}

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <cassert>

struct Pair {
    char item; int pos;
};

inline bool operator<(const Pair& a, const Pair& b) {
    return a.item < b.item || (a.item == b.item && a.pos < b.pos);
}

std::string fast(const std::string& s, const int k) {
    const int n = s.size();
    int last = -1;
    std::vector<bool> in(n);    
    std::string answ;
    std::set<Pair> set;
    for (int i = 0; i < n; ++i) {
        // Добавляем в std::set всех кандидатов:
        while (last+1-i <= k && last+1 < n) {
            ++last;
            set.insert(Pair{s[last],last});
            in[last] = true;
        }
        // Кандидат на вставку - текущий минимум:
        auto it = set.begin();
        // Если есть элемент, который двигать нельзя, то кандидатом становится он:
        if (i-k >= 0 && in[i-k]) {
            it = set.find(Pair{s[i-k], i-k});
            assert(it != set.end());   
        }
        // Вставляем элемент в ответ:
        answ.push_back(it->item);
        // Удаляем из std::set:
        in[it->pos] = false;
        set.erase(it);
    }
    return answ;
}

int main() {
    int k;
    scanf("%d", &k);
    
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string s(buf);
    
    printf("%s", fast(s, k).c_str());
    
    return 0;
}
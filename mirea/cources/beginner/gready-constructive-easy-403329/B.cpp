#include <iostream>
#include <functional>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::string s, t;
    std::cin >> n >> s >> t;
    std::vector<int> answ;
    for (int i = 0; i < n; ++i) {
        // инвариант: префикс длины i уже совпал
        // теперь надо, чтобы совпал i-й символ
        // чтобы получить минимум операций, необходимо найти ближайший
        // справа от i нужный символ в строке s и протащить его на i-ю позицию
        int p = int(std::find(s.begin()+i, s.end(), t[i]) - s.begin());
        if (p == n) {
            std::cout << "-1";
            return 0;
        }
        // протаскиваем символ с позиции p к позиции i:
        while (p > i) {
            answ.push_back(p);
            std::swap(s[p-1], s[p]);
            --p;
        }
    }
    std::cout << answ.size() << '\n';
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}
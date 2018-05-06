/*
    Динамическое программирование:
        len(it) = len(it-1)+1, если it-1 есть в массиве и расположен левее элемента it
    Затем восстановим ответ по известным длинам
*/

#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    int n; std::cin >> n;
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    
    std::vector<int> maxLen(n, 1);
    std::map<int, int> lastIndex;
    lastIndex[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
        auto it = lastIndex.find(a[i]-1);
        if (it != lastIndex.end()) {
            maxLen[i] = maxLen[it->second]+1;
        }
        lastIndex[a[i]] = i;
    }

    auto t = int(std::max_element(maxLen.begin(), maxLen.end()) - maxLen.begin());
    std::vector<int> answ{t};
    while (maxLen[t] != 1) {
        for (int s = t-1; s >= 0; --s) {
            if (a[s] == a[t]-1) {
                answ.push_back(s);
                t = s;
                break;
            }
        }
    }
    std::cout << answ.size() << std::endl;
    std::reverse(answ.begin(), answ.end());
    for (auto& it : answ) {
        std::cout << it+1 << " ";
    }
    std::cout << std::endl;
    return 0;
}
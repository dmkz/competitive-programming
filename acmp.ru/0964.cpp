/*
    Задача: 964. Ничего не потерялось
    
    Решение: std::map, std::set, строки, структуры данных, обработка запросов, O(n * log(n) * MXLEN)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    std::map<std::string, std::set<std::string>> map;
    for (int n; std::cin >> n; ) {
        for (int i = 0; i < n; ++i) {
            if (i > 0) { std::cout << "=====\n"; }
            std::string s; std::cin >> s;
            if (s == "Add") {
                std::cin >> s >> s;
                assert(s.front() == '\"' && s.back() == '\"');
                s.erase(s.begin());
                s.erase(std::prev(s.end()));
                auto& curr = map[s];
                std::cin >> s >> s;
                auto it = curr.find(s);
                if (it != curr.end()) { std::cout << "Already exists\n"; }
                else { curr.insert(s); std::cout << "OK\n"; }
            } else if (s == "Remove") {
                std::cin >> s >> s;
                assert(s.front() == '\"' && s.back() == '\"');
                s.erase(s.begin());
                s.erase(std::prev(s.end()));
                auto& curr = map[s];
                std::cin >> s >> s;
                auto it = curr.find(s);
                if (it == curr.end()) { std::cout << "Not found\n"; }
                else { curr.erase(it); std::cout << "OK\n"; }
            } else if (s == "Search") {
                std::cin >> s;
                assert(s.front() == '\"' && s.back() == '\"');
                s.erase(s.begin());
                s.erase(std::prev(s.end()));
                auto& curr = map[s];
                std::cout << "Results: " << curr.size() << " site(s) found\n";
                int cnt = 0;
                for (auto it = curr.begin(); cnt < 10 && it != curr.end(); it++) {
                    cnt++;
                    std::cout << cnt << ") " << *it << "\n";
                }
            }
        }
    }
    return 0;
}
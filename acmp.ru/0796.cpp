/*
    Задача: 796. Форматирование текста
    
    Решение: строки, разбор строк, анализ текста, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

typedef std::list<std::string> ls;

bool isSpaces(const std::string& s) {
    for (auto it : s) {
        if (!std::isspace(it)) {
            return false;
        }
    }
    return true;
}

ls read() {
    ls ret;
    std::string cur;
    while (std::cin && cur.empty()) {
        cur.clear();
        std::getline(std::cin, cur); 
        if (isSpaces(cur)) { cur.clear(); }
    }
    while (std::cin && !cur.empty()) {
        std::stringstream ss(cur);
        cur.clear();
        while (ss >> cur) { 
            ret.push_back(cur);
            assert(!cur.empty());
        }
        cur.clear();
        std::getline(std::cin, cur);
        if (isSpaces(cur)) { cur.clear(); }
    }
    return ret;
}

bool isComma(char c) {
    return c == 44 || c == 46 || c == 63 || c == 33 || c == 45 || c == 58 || c == 39;
}

void solve(const int w, const int b) {
    ls data = read();
    if (data.empty()) { return; }
    std::string s(b, ' ');
    for (auto it = data.begin(); it != data.end(); it++) {
        for (int i = 0; i + 1 < (int)it->size(); ++i) {
            if (isComma((*it)[i]) && !isComma((*it)[i+1])) {
                assert(!std::isspace((*it)[i+1]));
                data.insert(std::next(it), it->substr(i+1));
                it->resize(i+1);
                break;
            }
        }
    }
    for (auto it = data.begin(); std::next(it) != data.end(); ) {
        auto next = std::next(it);
        int last = 0;
        while (last < (int)next->size() && isComma((*next)[last])) {
            ++last;
        }
        *it += next->substr(0, last);
        next->erase(0, last);
        if (next->empty() || isSpaces(*next)) {
            data.erase(next);
        } else {
            it = next;
        }
    }
    for (auto it = data.begin(); it != data.end(); ) {
        if (int(s.size() + it->size()) <= w) {
            s += *it;
            s += " ";
            it++;
        } else {
            if (s.back() == ' ') { s.pop_back(); }
            std::cout << s << '\n';
            s = "";
        }
    }
    if (s.empty()) return;
    if (s.back() == ' ') { s.pop_back(); }
    assert(!s.empty());
    std::cout << s << '\n';
    s = "";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int w, b; std::cin >> w >> b;
    while (std::cin) { solve(w,b); }
    return 0;
}
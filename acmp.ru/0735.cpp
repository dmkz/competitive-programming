/*
    Задача: 735. Циклическое k-расширение
    
    Решение: строки, динамическое программирование, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

typedef std::vector<int> vi;

bool solve(const std::string& s, const std::string& t) {
    vi can(isz(t)+1);
    can[isz(t)]=true;
    for (int i = isz(t)-1; i >= 0; --i) {
        int j = 0;
        while (j < isz(s) && i+j < isz(t) && t[i+j] == s[j]) {
            can[i] = can[i] || can[i+j+1];
            ++j;
        }
    }
    vi queue, temp;
    for (int i = 0; i < isz(s); ++i) {
        if (s[i] == t[0]) {
            queue.push_back(i);
        }
    }
    bool answ = can[0];
    for (int len = 1; len <= isz(t); ++len) {
        temp.clear();
        for (int i : queue) {
            answ = answ || can[len];
            if (i + 1 < isz(s) && len < isz(t) && s[i+1] == t[len]) {
                temp.push_back(i+1);
            }
        }
        queue = temp;
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s, t; std::cin >> s >> t; std::cout << (solve(s,t) ? "YES\n" : "NO\n"));
    return 0;
}
/*
    Задача: 848. Заклинание Ауэрса
    
    Решение: динамическое программирование, строки, O(n^3)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

bool is_palindrome(std::string s) {
    for (int i = 0, j = (int)s.size()-1; i <= j; ++i,--j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

const int INF = (int)1e9+1;

int main() {
    std::string s; 
    while (std::cin >> s) {
        const int n = (int)s.size();
        std::vector<int> min(1+n, INF), from(1+n, -1);
        min[0] = 0, from[0] = 0;
        for (int len = 1; len <= n; ++len) {
            for (int sub = 1; sub <= len; ++sub) {
                int j = len-1;
                int i = j - sub + 1;
                if (is_palindrome(s.substr(i, sub))) {
                    int val = min[i] + 1;
                    if (min[len] > val) {
                        min[len] = val;
                        from[len] = i;
                    }
                }
            }
        }
        std::vector<std::string> answ;
        for (int len = n; len > 0; ) {
            answ.push_back(s.substr(from[len]));
            s.resize(from[len]);
            len = from[len];
        }
        std::reverse(answ.begin(), answ.end());
        std::cout << answ.size() << "\n";
        for (auto& it : answ) std::cout << it << "\n";
    }
    return 0;
}
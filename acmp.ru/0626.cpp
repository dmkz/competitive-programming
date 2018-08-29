/*
    Задача: 626. Преобразователь строк
    
    Решение: реализация, строки, stack, O(len)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <string>
#include <vector>

int main() {
    int n; scanf("%d", &n);
    static bool erase[26][26];
    for (int i = 0; i < n; ++i) {
        char a, b; scanf(" %c %c", &a, &b);
        int f = a - 'a', s = b - 'a';
        erase[f][s] = true;
    }
    std::vector<char> stack;
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string s(buf);
    for (auto it : s) {
        if (stack.empty()) {
            stack.push_back(it);
            continue;
        }
        int i = stack.back()-'a';
        int j = it - 'a';
        if (erase[i][j]) {
            stack.pop_back();
        } else {
            stack.push_back(it);
        }
    }
    s = std::string(stack.begin(), stack.end());
    printf("%s", s.c_str());
    return 0;
}
#include <bits/stdc++.h>

int main() {
    int n, k; std::cin >> n >> k;
    std::string t; std::cin >> t;
    // строим строку s. изначально полагаем s := t. Это уже одно вхождение
    std::string s = t;
    --k;
    // теперь рассматриваем все позиции начиная с 1 слева-направо и
    // пробуем поставить в них нашу строку t
    int p = 1;
    while (k > 0) {
        if (p == size(s)) {
            // если дошли до конца s, то приписываем t и это ещё одно вхождение
            s += t;
            --k;
        } else {
            // иначе, если суффикс s совпал с префиксом t
            // то мы дописываем в строку s остальные символы,
            // расположенные за префиксом t
            int len = std::min(size(s)-p, size(t));
            auto temp = s.substr(p, len);
            if (temp == t.substr(0, len)) {
                s += t.substr(len);
                --k;
            }
        }
        ++p;
    }
    std::cout << s;
    return 0;
}
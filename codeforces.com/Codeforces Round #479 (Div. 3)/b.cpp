#include <bits/stdc++.h>

int main() {
    scanf("%*d");
    std::string s; std::cin >> s;
    // Посчитаем количество всех подстрок длины 2:
    std::map<std::string, int> count;
    for (int i = 0; i < (int)s.size()-1; ++i) {
        count[s.substr(i, 2)]++;
    }
    // Найдем максимум:
    int max_count = 0; std::string max_s;
    for (auto& it : count) {
        if (it.second > max_count) {
            max_s = it.first;
            max_count = it.second;
        }
    }
    // Вывод ответа:
    std::cout << max_s << std::endl;
    return 0;
}
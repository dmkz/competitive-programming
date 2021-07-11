#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем входные данные и записываем в std::deque:
    std::string s; std::cin >> s;
    std::deque<char> d(all(s));
    // deque пригодится так как он умеет добавлять в начало и в конец за O(1)
    // можно было использовать std::list<char> - умеет то же самое
    // два метода добавления в конец и в начало
    // при запросе на реверс будет их свапать:
    // добавление в начало будет добавлением в конец и наоборот
    std::function<void(char)> push_back = [&](char c) {
        d.push_back(c);
    };
    std::function<void(char)> push_front = [&](char c) {
        d.push_front(c);
    };
    // читаем запросы
    int q,isReversed=0; std::cin >> q;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) isReversed ^= 1, std::swap(push_back, push_front); // свапаем методы
        else {
            // добавляем один символ в указанном направлении:
            char newChar;
            std::cin >> t >> newChar;
            if (t == 1) push_front(newChar);
            else push_back(newChar);
        }
    }
    // выводим ответ:
    s.assign(all(d));
    if (isReversed) std::reverse(all(s));
    std::cout << s << std::endl;
    return 0;
}
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using pll = std::pair<ll,ll>;
void solveEasy() {
    // читаем отрезки:
    std::vector<pll> segs;
    std::string s;
    while (std::getline(std::cin, s)) {
        size_t p = s.find('-');
        if (p == s.npos)
            break;
        ll L = std::stoll(s.substr(0, p));
        ll R = std::stoll(s.substr(p+1));
        segs.emplace_back(L, R);
    }
    // читаем запросы:
    std::vector<ll> questions;
    while (std::getline(std::cin, s) && s.size()) {
        ll p = std::stoll(s);
        questions.emplace_back(p);
    }
    // создаём события:
    const int DEL = 0, ADD = 1, ASK = 2;
    std::vector<std::pair<ll, int>> events;
    for (const auto &[L, R] : segs) {
        events.emplace_back(L, ADD);
        events.emplace_back(R+1, DEL);
    }
    for (const auto &p : questions)
        events.emplace_back(p, ASK);
    // сортируем события:
    std::sort(all(events));
    // обрабатываем отсортированные события:
    int count = 0, answ = 0;
    for (const auto &[p, t] : events) {
        if (t == ADD) count++;
        else if (t == DEL) count--;
        else {
            assert(t == ASK);
            answ += (count > 0);
        }
    }
    std::cout << answ << std::endl;
}
void solveHard() {
    // читаем отрезки:
    std::vector<pll> segs;
    std::string s;
    while (std::getline(std::cin, s)) {
        size_t p = s.find('-');
        if (p == s.npos)
            break;
        ll L = std::stoll(s.substr(0, p));
        ll R = std::stoll(s.substr(p+1));
        segs.emplace_back(L, R);
    }
    // сортируем отрезки:
    std::sort(all(segs));
    // объединяем отсортированные отрезки:
    ll answ{};
    for (int i = 0, j; i < isz(segs); i = j) {
        ll L = segs[i].first, R = segs[i].second;
        for (j = i; j < isz(segs) && R >= segs[j].first; j++)
            R = std::max(R, segs[j].second);
        answ += R - L + 1;
    }
    std::cout << answ << std::endl;
}
main() {
    solveHard();
}

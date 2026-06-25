// перебор, реализация, комбинаторика
// Задача: B, Вердикт: OK, Время: 218ms, Память: 136.00Kb
#include <bits/stdc++.h>
using vi = std::vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
std::vector<std::string> answer;
void precalc() {
    answer.assign(1001, "Z");
    for (int x = 0; x < 1000000; x++) {
        vi cnt(10); std::string temp;
        for (int t = x, i = 0; i < 6; i++) {
            temp += char('0' + t % 10);
            cnt[t % 10]++;
            t /= 10;
        }
        int n = 10;
        for (int i = 0; i < 10; i++)
            if (cnt[i] > 0)
                n--;
        // AAA <-- n
        // AAB <-- n*(n-1)
        // ABA <-- n*(n-1)
        // ABB <-- n*(n-1)
        // ABC <-- n*(n-1)*(n-2)
        int case1 = n;
        std::string s1 = "A"+temp.substr(0, 3)+"AA"+temp.substr(3);
        remin(answer[case1], s1);
        int case2 = n*(n-1);
        std::string s2 = "A"+temp.substr(0, 3)+"AB"+temp.substr(3);
        remin(answer[case2], s2);
        int case3 = n*(n-1)*(n-2);
        std::string s3 = "A"+temp.substr(0, 3)+"BC"+temp.substr(3);
        remin(answer[case3], s3);
    }
}
void solve() {
    int x; std::cin >> x;
    if (answer[x] == "Z") std::cout << "-1\n";
    else std::cout << answer[x] << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    precalc();
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}

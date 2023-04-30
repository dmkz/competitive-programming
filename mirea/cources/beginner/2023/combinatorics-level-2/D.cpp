#include <bits/stdc++.h>
using namespace std;
int64_t C_n_2(int n) {
    return n * (n-1LL) / 2;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // надо добавлять ампулу, удалять и сообщать ответ
    int64_t answ{};
    vector<int> cnt(1+n);
    auto add = [&](int item, int delta = 1) {
        // вычитаем то, что входило в ответ:
        answ -= C_n_2(cnt[item]);
        // меняем слагаемое:
        cnt[item] += delta;
        // добавляем то, что теперь входит в ответ:
        answ += C_n_2(cnt[item]);
    };
    auto rem = [&](int item) {
        return add(item, -1);
    };
    // добавляем все ампулы в ответ:
    for (auto it : a)
        add(it);
    // теперь будем удалять i-й, сообщать ответ, и возвращать i-й обратно:
    for (int i = 0; i < n; i++) {
        rem(a[i]);
        cout << answ << ' ';
        add(a[i]);
    }
}

#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    auto sorted = a;
    sort(sorted.begin(), sorted.end());
    vector<int> used(n);
    // переберём каждый отрезок из двух и более элементов и проверим
    // что сумма на нём есть в массиве (бинарным поиском)
    for (int i = 0; i + 1 < n; i++) {
        int s = a[i];
        for (int j = i + 1; j < n; j++) {
            s += a[j];
            // ищем сумму бинпоиском в векторе посорченных элементов:
            auto iter = lower_bound(sorted.begin(), sorted.end(), s);
            if (iter != sorted.end() && *iter == s)
                used[iter - sorted.begin()] = 1; // отмечаем этот элемент
        }
    }
    // считаем ответ (сколько элементов отмечены)
    int answer = 0;
    for (auto item : a) {
        auto iter = lower_bound(sorted.begin(), sorted.end(), item);
        answer += used[iter - sorted.begin()];
    }
    cout << answer << "\n";   
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}

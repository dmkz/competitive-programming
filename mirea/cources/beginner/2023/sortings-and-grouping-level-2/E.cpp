#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n; // n паровозиков
        vector a(n, vector<int>()); // паровозики будем хранить в векторе из векторов
        for (int i = 0, k; i < n; i++) {
            // читаем i-й паровозик в данном формате
            cin >> k;
            a[i].resize(k);
            for (auto &it : a[i])
                cin >> it;
        }
        // сортируем паровозики:
        sort(a.begin(), a.end());
        // выводим паровозики в том же формате:
        for (auto &train : a) {
            cout << train.size();
            for (auto &item : train)
                cout << ' ' << item;
            cout << '\n';
        }
    }
}
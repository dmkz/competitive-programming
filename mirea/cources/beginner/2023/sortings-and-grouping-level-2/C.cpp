#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные:
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // отсортируем по возрастанию:
    sort(a.begin(), a.end());
    // добавим в конец бесконечность:
    a.push_back((int)1e9+1);
    // берём k-е число (в 0 индексации) минус 1:
    const int take = a[k]-1;
    // проверяем его:
    // 1. должны взять натуральное число
    // 2. (k-1)-й элемент должен быть <= взятого, так как k-й гарантированно < взятого
    if (take >= 1 && (k == 0 || a[k-1] <= take))
        cout << take << '\n';
    else
        cout << "-1\n";
}
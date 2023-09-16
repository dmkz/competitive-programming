#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
int main() {
    // ускоряем ввод-вывод:
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int n; cin >> n;
    vl V(n), T(n);
    for (auto &it : V) cin >> it;
    for (auto &it : T) cin >> it;
    // будем поддерживать множество живых сугробов
    // мы будем помнить, на какую величину надо уменьшить все сугробы в множестве
    // чтобы не уменьшать их каждый раз
    multiset<ll> alive;
    ll accumulatedT = 0;
    for (int i = 0; i < n; i++) {
        alive.insert(accumulatedT + V[i]);
        ll nextT = (accumulatedT + T[i]);
        // все те сугробы, объём которых <= nextT, растают сегодня
        ll total = 0;
        while (alive.size() && *alive.begin() <= nextT) {
            auto curr = *alive.begin();
            alive.erase(alive.begin());
            total += (curr - accumulatedT);
        }
        accumulatedT = nextT;
        // все остальные уменьшатся на T[i]
        total += T[i] * alive.size();
        // выводим ответ и переходим к следующему дню
        cout << total << ' ';
    }
    cout << endl;
}

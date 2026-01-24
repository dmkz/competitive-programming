#include <iostream>
#include <vector>
#include <set>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
int main() {
    // читаем перестановку и запоминаем позиции каждого элемента:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi p(n), pos(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    // читаем враждебные пары, создаём отрезки [L, R] для сканлайна
    multiset<int> ends = {n}; // здесь будем хранить правые границы
                              // всё ещё открытых отрезков
    vvi del(n+1); // del[L] = список правых границ для данного L
    while (m --> 0) {
        int a, b; cin >> a >> b;
        a--, b--;
        int L = pos[a], R = pos[b];
        if (L > R) swap(L, R);
        del[L].push_back(R);
        ends.insert(R);
    }
    // Рассмотрим все отрезки, начинающиеся в i, и пусть есть множество
    // правых границ. Тогда все отрезки, заканчивающиеся до минимальной
    // правой границе, нам подходят, так как не будут содержать ни одну
    // враждебную пару.
    ll answ{};
    for (int i = 0; i < n; i++) {
        // кол-во способов выбрать правую границу:
        answ += *ends.begin() - i;
        // при переходе от i к (i+1) закрываем отрезки,
        // начинающиеся в точке i.
        for (int R : del[i])
            ends.erase(ends.find(R));
    }
    cout << answ << endl;
}
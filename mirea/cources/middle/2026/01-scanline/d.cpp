#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using vl = vector<ll>;
template<typename T>
using PQLess = priority_queue<T, vector<T>, greater<T>>;
using Query = pair<ll, int>;
int main() {
    // читаем данные и сортируем их:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vl s(n); for (auto &it : s) cin >> it;
    sort(all(s));
    // ответ для [L, R] равен ответу для [L+1, R+1], поэтому
    // ответ зависит только от длины отрезка.
    // Начиная с длины len = s[i+1] - s[i], соседние струны начинают
    // генерировать повторы. Они сливаются. Поэтому можем считать их
    // как одну струну. Пример: струны 3 и 5.
    // Длина 1:
    // 3
    // 5
    // Длина 2:
    // 34
    // 56
    // Длина 3:
    // 345 <-- дальше будут только повторы: 6, 7, 8, 9, ...
    // 567
    // Обрабатываем запросы в порядке возрастания длины.
    // Два типа запросов:
    // 1) {len, -1} <-- объединяем две соседние струны
    // 2) {len, id} <-- записываем ответ на запрос длины len
    // Ответ считаем так:
    // предыдущий ответ += (количество уникальных струн) * (разница длин)
    
    // кидаем запросы на объединение струн:
    PQLess<Query> pq;
    for (int i = 1; i < isz(s); i++)
        pq.push(Query{s[i] - s[i-1], -1});
    
    // кидаем запросы на кол-во чисел на отрезке:
    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        ll L, R; cin >> L >> R;
        ll len = R - L + 1;
        pq.push(Query{len, i});
    }
    // обработка запросов:
    ll lastLen = 0, lastAnsw = 0; // последний ответ
    vl answ(1+q);
    while (pq.size()) {
        auto [currLen, currId] = pq.top();
        pq.pop();
        // обновляем последний ответ:
        if (lastLen < currLen) {
            lastAnsw += (currLen - lastLen) * n;
            lastLen = currLen;
        }
        // обрабатываем текущий запрос:
        if (currId < 0) n--; // слияние двух струн
        else answ[currId] = lastAnsw;
    }
    // выводим ответы
    for (int i = 1; i <= q; i++)
        cout << answ[i] << ' ';
    cout << endl;
}
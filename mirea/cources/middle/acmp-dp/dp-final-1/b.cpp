#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
const ll inf = (ll)1e18L;
int main() {
    // читаем данные + считаем динамику
    int n, S; cin >> n >> S;
    // dp[i][s] = максимальная токсичность предложения длины s, если
    // мы используем первые i слов
    // используем двуслойную динамику:
    // prev - это dp[i-1]
    // curr - это dp[i]
    vector curr(S+1, -inf);
    curr[0] = 0; // токсичность предложения длины 0 равна 0 - инициализация dp
    for (int i = 1; i <= n; i++) {
        // читаем параметры i-го слова
        int currLen, currToxic;
        cin >> currLen >> currToxic;
        // копируем предыдущий слой и создаём новый
        auto prev = curr;
        curr.assign(S+1, -inf);
        // считаем динамику
        for (int s = 0; s <= S; s++) {
            // мы можем взять i-е слово, или не брать его
            if (s >= currLen) // вариант, когда берем i-е слово
                curr[s] = prev[s - currLen] + currToxic;
            // вариант, когда не берём i-е слово
            curr[s] = max(curr[s], prev[s]);
        }
    }
    // выводим ответ
    cout << *max_element(all(curr)) << endl;
}

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
const ll inf = (ll)1e18L;
const int TMAX = 100100;
int main() {
    // читаем данные + считаем динамику
    int n, S; cin >> n >> S;
    // dp[i][t] = минимальная длина предложения, обладающего токсичностью t, если
    // мы используем первые i слов
    // используем двуслойную динамику:
    // prev - это dp[i-1]
    // curr - это dp[i]
    vector curr(TMAX+1, inf);
    curr[0] = 0; // длина предложения токсичности 0 равна 0 - инициализация dp
    for (int i = 1; i <= n; i++) {
        // читаем параметры i-го слова
        int currLen, currToxic;
        cin >> currLen >> currToxic;
        // копируем предыдущий слой и создаём новый
        auto prev = curr;
        curr.assign(TMAX+1, inf);
        // считаем динамику
        for (int t = 0; t <= TMAX; t++) {
            // мы можем взять i-е слово, или не брать его
            if (t >= currToxic) // вариант, когда берем i-е слово
                curr[t] = prev[t - currToxic] + currLen;
            // вариант, когда не берём i-е слово
            curr[t] = min(curr[t], prev[t]);
        }
    }
    // выводим ответ: надо найти максимальную токсичность для длины <= S:
    int maxToxic = TMAX;
    while (maxToxic >= 0 && curr[maxToxic] > S)
        maxToxic--;
    assert(maxToxic >= 0); // проверка на то что ответ вообще нашёлся
    cout << maxToxic << endl;
}

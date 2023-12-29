#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
/*
    можем ли мы получить ответ, который делится на x?
    да, если для каждого i в отрезке [ai-k, ai] есть число
    которое делится на x
    переберём все x
        для этого x переберём числа вида n * x
        // если у нас есть отрезок, который избегает все числа
        // вида n * x, то нельзя
        // ai-k > n * x
        // ai > n * x + k
        // ai < (n+1) * x
        // есть ли ai вот такие вот:
        // n * x + k < ai < (n+1) * x
*/
const int AMAX = (int)10e6+100;
using vi = vector<int>;
main() {
    // чтение:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vi a(n);
    for (auto &it : a)
        cin >> it;
    // сортируем + считаем префикс-суммы:
    sort(all(a));
    int answ = 0;
    vi s(AMAX);
    for (auto &it : a) {
        answ = gcd(answ, it);
        s[it]++;
    }
    for (int i = 1; i < AMAX; i++)
        s[i] += s[i-1];
    // сколько элементов массива со значениями от L до R:
    auto countElements = [&](int L, int R) {
        if (R >= isz(s)) R = isz(s)-1;
        return L <= R ? s[R] - s[L-1] : 0;
    };
    // перебираем каждый возможный gcd и проверяем его:
    const int amax = *min_element(all(a));
    for (int x = 1; x <= amax; x++) {
        bool ok = 1;
        for (int n = 0; n * x + k < AMAX; n++) {
            if (countElements(n * x + k + 1, (n+1) * x - 1)) {
                ok = false;
                break;
            }
        }
        if (ok) answ = x;
    }
    cout << answ << endl;
}

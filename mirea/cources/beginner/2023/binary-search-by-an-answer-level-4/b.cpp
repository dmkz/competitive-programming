#include <bits/stdc++.h>

#define isz(x) (int)(x).size()

using namespace std;
using vi = vector<int>;

int check(const vi &a, int k, int len) {
// проверяем можно ли получить отрезок длины len
// состоящий из единиц
    int nZeros = 0, i = 0;
    while (i < len)
        nZeros += (a[i++] == 0);
    if (nZeros <= k)
        return i-len;
    while (i < isz(a)) {
        // двигаем на 1 вправо
        nZeros -= (a[i-len] == 0);
        nZeros += (a[i++] == 0);
        if (nZeros <= k)
            return i-len;
    }
    return -1;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (auto &it : a)
        cin >> it;
    // бинарный поиск по длине отрезка
    // ответ лежит на отрезке [0, n]
    int low = -1, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a,k,mid) != -1) low = mid;
        else high = mid;
    }
    // нашли ответ в виде длины отрезка
    // надо найти позицию, выставить 1 и вывести ответ
    cout << low << endl;
    int pos = check(a, k, low);
    for (int i = 0; i < low; i++)
        a[i+pos] = 1;
    for (auto &it : a)
        cout << it << ' ';
    cout << endl;
}

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using vi = vector<int>;
int check(const vi &a, int k, int len) {
// проверяет есть ли k-хороший подотрезок длины len
// возвращает начало этого отрезка, либо -1, если его нет
    vi cnt((int)1e6+1);
    int nUnique = 0;
    auto add = [&](int item) {
        cnt[item]++;
        nUnique += (cnt[item] == 1);
    };
    auto rem = [&](int item) {
        cnt[item]--;
        nUnique -= (cnt[item] == 0);
    };
    // формируем начальный отрезок [0, len)
    int i = 0;
    while (i < len)
        add(a[i++]);
    // проверяем его:
    if (nUnique <= k)
        return i - len;
    // далее проверяем каждый из оставшихся отрезков длины len:
    while (i < isz(a)) {
        rem(a[i-len]);
        add(a[i++]);
        if (nUnique <= k)
            return i - len;
    }
    return -1;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int n, k; cin >> n >> k;
    vi a(n);
    for (auto &it : a)
        cin >> it;
    // дальше бинпоиск по ответу - по длине этого отрезка:
    int low = -1, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a,k,mid) != -1) low = mid;
        else high = mid;
    }
    // выводим границы ответа:
    assert(low != -1);
    int left = check(a,k,low);
    assert(left != -1);
    cout << left + 1 << ' ' << left+low << endl;
} 

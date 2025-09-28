#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
// корневая декомпозиция для операций:
// - присвоения по индексу i: a[i] = x
// - суммы на отрезке от L до R
template<int gsize>
struct SqrtDec {
    std::vector<int> arr;
    std::vector<ll> gsum;
    SqrtDec(const std::vector<int> &arr_)
        : arr(arr_)
        , gsum((isz(arr)+gsize-1)/gsize)
    {
        for (int i = 1; i < isz(arr); i++)
            gsum[i / gsize] += arr[i];
    }
    void set(int i, int x) {
        (gsum[i / gsize] -= arr[i]) += x;
        arr[i] = x;
    }
    void setmin(int i, int x) {
        set(i, std::min(arr[i], x));
    }
    ll getsum(int l, int r) const {
        int gl = l / gsize, gr = r / gsize;
        if (gl == gr) {
            ll res = 0;
            for (int i = l; i <= r; i++)
                res += arr[i];
            return res;
        } else {
            ll res = 0;
            for (int i = l; i < (gl+1)*gsize; i++)
                res += arr[i];
            for (int g = gl+1; g < gr; g++)
                res += gsum[g];
            for (int i = gr * gsize; i <= r; i++)
                res += arr[i];
            return res;
        }
    }
};
void solve() {
    // идея: для каждого k мы можем хранить индексы ячеек, которые мы должны будем
    // обновить при следующем запросе вида 1 k. Изначально это все индексы
    // Их суммарно n log(n) -- гармонический ряд:
    // n / 1 + n/2 + n/3 + ... + n/k + ... + n / n = O(n log(n))
    // Когда приходит запрос "1 k" мы обновляем только ячейки из этого списка
    // Когда приходит запрос "2 i x", мы обновляем a[i] = x и для каждого делителя
    // числа i запоминаем, что в следующий раз, когда будет запрос "1 k", надо
    // обновить ячейку i. Количество делителей O(cbrt(i))
    // Поэтому асимптотика O(n sqrt(n)) за счёт корневой декомпозиции - суммы на отрезке
    // Обновление по индексу делается за O(1) в корневой
    int n; std::cin >> n;
    std::vector<int> a(1 + n);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    SqrtDec<256> sd(a);
    std::vector<std::vector<int>> divisors(1+n);
    std::vector<std::vector<int>> modified(1+n);
    for (int j = 1; j <= n; j++)
        for (int k = j; k <= n; k += j) {
            divisors[k].push_back(j);
            modified[j].push_back(k);
        }
    auto setmin = [&](int i, int x) {
        sd.setmin(i, x);
    };
    auto set = [&](int i, int x) {
        sd.set(i, x);
    };
    auto getSum = [&](int L, int R) {
        return sd.getsum(L, R);
    };
    int q; std::cin >> q;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int k; std::cin >> k;
            // вот тут нам нужно пройти только активные ячейки
            for (int i : modified[k])
                setmin(i, k);
            modified[k].clear();
        } else if (t == 2) {
            int i, x; std::cin >> i >> x;
            for (int j : divisors[i]) {
                modified[j].push_back(i);
                set(i, x);
            }
        } else {
            assert(t == 3);
            int l, r; std::cin >> l >> r;
            std::cout << getSum(l, r) << "\n";
        }
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}

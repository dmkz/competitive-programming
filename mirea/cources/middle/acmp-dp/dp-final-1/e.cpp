#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
const int mod = 998244353;
const int NMAX = 200200;
using pii = pair<int,int>;

// вычитание из числа по модулю
void subfrom(int &a, int b) {
    a -= b;
    if (a < 0)
        a += mod;
}

// умножение по модулю
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}

// быстрое возведение в степень (a^k)
int binpow(int a, int k) {
    int res = 1;
    while (k > 0) {
        if (k % 2 == 1)
            res = mul(res, a);
        a = mul(a, a);
        k >>= 1;
    }
    return res;
}

// предподсчёт факториалов (n!)
const vector<int> fact = [](){
    vector<int> result(NMAX+1, 1);
    for (int i = 1; i <= NMAX; i++)
        result[i] = mul(result[i-1], i);
    return result;
}();

// предподсчёт обратных факториалов (1/n!)
const vector<int> ifact = [](){
    vector<int> result(NMAX+1, 1);
    result[NMAX] = binpow(fact[NMAX], mod-2);
    for (int i = NMAX-1; i >= 0; i--)
        result[i] = mul(result[i+1], i+1);
    return result;
}();

int C(int n, int k) {
// биномиальный коэффициент C из n по k
    if (k < 0 || k > n || n < 0)
        return 0;
    return mul(fact[n], mul(ifact[k], ifact[n-k]));
}

int countWays(int r1, int c1, int r2, int c2) {
// количество путей между точками (r1,c1) и (r2,c2)
    return C(r2-r1+c2-c1, r2-r1);
}

int main() {
    // читаем данные
    int n, m, k;
    cin >> n >> m >> k;
    vector<pii> a(k);
    for (auto &[r,c] : a)
        cin >> r >> c;
    // сортируем точки
    sort(all(a));
    // размеры поля очень большие
    // ловушек мало. поэтому из всех путей будем считать те,
    // которые проходят через ловушки
    
    // dp[i] = кол-во путей, которые закончились в i-й точке и не попали
    // ни в одну ловушку до неё
    a.emplace_back(n, m); // добавляем точку назначения как фиктивную ловушку
    vector<int> dp(isz(a));
    for (int i = 0; i < isz(dp); i++) {
        auto [ri, ci] = a[i];
        // число путей дойти от (1, 1) до i-й точки:
        int result = countWays(1, 1, ri, ci);
        // вычитаем пути, которые проходят через ловушки:
        for (int j = 0; j < i; j++)
            if (auto [rj, cj] = a[j]; rj <= ri && cj <= ci)
                // вычитаем путь, который:
                // 1. проходит через j-ю ловушку
                // 2. не проходит ни через какую ловушку до j-й (инвариант динамики)
                subfrom(result, mul(dp[j], countWays(rj, cj, ri, ci)));
        // посчитали ответ для i-й точки:    
        dp[i] = result;
    }
    // выводим ответ
    cout << dp.back() << endl;
}

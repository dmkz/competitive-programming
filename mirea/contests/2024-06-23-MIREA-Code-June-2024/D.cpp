#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
using Vec = vector<int>;
using Mat = vector<Vec>;
using ll = long long;
// умножение двух матриц
Mat operator*(const Mat &a, const Mat &b) {
    Mat c(a.size(), Vec(b[0].size()));
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b[0].size(); j++)
            for (int k = 0; k < (int)a[0].size(); k++)
                (c[i][j] += a[i][k] * 1LL* b[k][j] % mod) %= mod;
    return c;
}
// умножение матрицы на вектор
Vec operator*(const Mat &a, const Vec &b) {
    Vec c(a.size());
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)a[0].size(); j++)
            (c[i] += a[i][j] * 1LL * b[j] % mod) %= mod;
    return c;
}
// быстрое возведение матрицы в степень
Mat binpow(Mat a, ll n) {
    Mat r(a.size(), Vec(a.size()));
    for (int i = 0; i < (int)r.size(); i++)
        r[i][i] = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = r * a;
        a = a * a;
        n >>= 1;
    }
    return r;
}
int solve(ll n)
{
    // пусть прямо сейчас у нас b синих шестиугольников и w белых
    // распишем что произойдёт через 1 секунду
    //  {b, w} -> {w, b} + {b, w} + {w, b} + {b, w} + {w, b} + {b, w} + {w, b}
    //            мутация           мутация           мутация           мутация
    // собирая слагаемые, получаем:
    //  {b, w} -> {3 * b + 4 * w, 4 * b + 3 * w}
    // запишем в матричном виде:
    //  [b] =  [3 4] * [b]
    //  [w]    [4 3]   [w]
    // итого, обозначив эту матрицу за A, получим, что через n секунд будет:
    // [b(n), w(n)] = A^n * [b(0), w(0)]
    // поэтому возводим матрицу в степень быстрым возведением в степень и считаем
    // финальный ответ
    Mat A = {{3,4},{4,3}};
    return (binpow(A,n)*Vec{1,0})[0];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        ll n; cin >> n;
        cout << solve(n) << "\n";
    }
}
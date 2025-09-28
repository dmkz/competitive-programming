#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

/*
    Сначала пишем решение динамическим программированием за O(n * k),
    затем сводим динамику к матричному виду и возведению матрицы в степень
    получая асимптотику O(log(n) * k^3)
    
    Для получения более быстрого решения:
    
    1) Если сильны в линейной алгербе, то матрицу A можно диагонализовать, перейдя
    к собственному базису A = S^{-1} * J * S и тогда возведение матрицы в степень:
    A^n = (S^{-1} * J * S)^n = S^{-1} * J^n * S, где J^n считается за O(log(n) * k)
    
    2) Иначе нужно думать в сторону решения комбинаторикой. Для этого внимательно
    смотрим на динамику O(n * k) и думаем как это посчитать комбинаторикой быстрее
    через биномиальные коэффициенты
*/

const int mod = (unsigned)1e9+7;

struct Mat {
    
    int n;
    std::vector<std::vector<int>> data;
    
    Mat(int n_) : n(n_), data(n, std::vector<int>(n, 0)) { }
    
    void toIdentity() {
        for (int i = 0; i < n; i++) {
            std::memset(data[i].data(), 0, sizeof(int) * 4);
            data[i][i] = 1;
        }
    }
    
    // круглые скобки вместо []
    int& operator()(int row, int col) { return data[row][col]; }
    const int& operator()(int row, int col) const { return data[row][col]; }

    
};

Mat mul(const Mat& A, const Mat& B) {
    assert(A.n == B.n);
    int n = A.n;
    Mat C(n);
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) if (A(i, k) != 0)
            for (int j = 0; j < n; j++) if (B(k, j) != 0)
                C(i, j) = int((C(i, j) + A(i, k) * 1LL * B(k, j)) % mod);
    return C;
}

Mat mpow(Mat base, unsigned long long e) {
    const int n = base.n;
    Mat res(n);
    res.toIdentity();
    while (e) {
        if (e & 1) res = mul(res, base);
        base = mul(base, base);
        e >>= 1;
    }
    return res;
}

int subsequence(int64_t n, int k) {
    Mat M(k+1);
    for (int i = 0; i < k; i++) {
        M(i,i) += 25;
        M(i+1,i) += 1;
    }
    M(k,k) += 26;
    Mat P = mpow(M, n);
    return P(k, 0);
}

void solve() {
    std::string name; int64_t n;
    std::cin >> name >> n;
    std::cout << subsequence(n, isz(name)) << '\n';
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}

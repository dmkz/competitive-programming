#include <bits/stdc++.h>

const int mod = (int)1e9+7;
int add(int a, int b) { return (a += b) >= mod ? a -= mod : a; }
int mul(int a, int b) { return int(1LL * a * b % mod); }
 
typedef std::vector<int> Vec;
typedef std::vector<Vec> Mat;
// скалярное произведение двух векторов:
int dot(const Vec& a, const Vec& b) {
    int res = 0;
    for (int i = 0; i < size(a); ++i) {
        res = add(res, mul(a[i], b[i]));
    }
    return res;
}
// умножение матрицы на вектор:
Vec matMultVec(const Mat& A, const Vec& b) {
    Vec res(size(A));
    for (int i = 0; i < size(A); ++i) {
        res[i] = dot(A[i], b);
    }
    return res;
}
// генерация рандомного вектора:
Vec randVec(int n) {
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, mod-1);
    Vec ret(n);
    for (auto &it : ret) 
        it = dist(gen);
    return ret;
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // чтобы проверить A*B==C за квадрат мы сгенерируем рандомный вектор v
    // и умножим матрицы на вектор. Умножение матрицы на вектор работает за
    // O(n^2). Таким образом, проверяем, что A*(B*v) == C * v
    // с высокой вероятностью если результат умножения совпал, то и матрицы равны
    int n; std::cin >> n;
    Mat A(n, Vec(n));
    auto B = A;
    auto C = B;
    for (auto &row : A) for (auto &it : row) { std::cin >> it; }
    for (auto &row : B) for (auto &it : row) { std::cin >> it; }
    for (auto &row : C) for (auto &it : row) { std::cin >> it; }
    Vec v = randVec(n);
    std::cout << (matMultVec(A, matMultVec(B, v)) == matMultVec(C, v) ? "YES\n" : "NO\n");
    return 0;
}
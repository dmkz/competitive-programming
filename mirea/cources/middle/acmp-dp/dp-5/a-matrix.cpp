#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;
using Vec = vector<int>;
using Mat = vector<Vec>;

const int mod = (int)1e9+7;

Vec operator*(const Mat &A, const Vec &b) {
    const int n = (int)A.size();
    Vec c(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            (c[i] += A[i][j] * 1LL * b[j]) %= mod;
        }
    return c;
}
Mat operator*(const Mat &A, const Mat &B) {
    const int n = (int)A.size();
    Mat C(n, Vec(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                (C[i][j] += A[i][k] *1LL* B[k][j]) %= mod;
    return C;
}
Mat binpow(Mat A, int k) {
    const int nRows = (int)A.size();
    Mat R(nRows, Vec(nRows, 0));
    for (int i = 0; i < nRows; i++)
        R[i][i] = 1;
    while (k > 0) {
        if (k % 2 == 1)
            R = R * A;
        A = A * A;
        k /= 2;
    }
    return R;
}
signed main() {
    // читаем данные
    int n, k; cin >> n >> k;
    vector<string> a(n);
    for (auto &it : a)
        cin >> it;
    // инициализируем динамику
    Vec dp(n*n, 0);
    dp[0] = 1;
    // строим матрицу перехода
    Mat A(n*n, Vec(n*n, 0)); // A[куда][откуда] = возможен переход или нет?
    for (int currRow = 0; currRow < n; currRow++)
        for (int currCol = 0; currCol < n; currCol++)
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (dr * dr + dc * dc == 1) {
                        int nextRow = currRow + dr;
                        int nextCol = currCol + dc;
                        if (nextRow < 0 || nextRow >= n)
                            continue;
                        if (nextCol < 0 || nextCol >= n)
                            continue;
                        if (a[nextRow][nextCol] == '1')
                            continue;
                        // проверили всё что можно
                        // теперь точно есть переход
                        // (currRow, currCol) --> (nextRow, nextCol)
                        A[nextRow * n + nextCol][currRow * n + currCol] = 1;
                    }
    // ответ:
    auto answer = binpow(A, k) * dp;
    cout << answer[(n-1)*n+(n-1)] << endl;
}

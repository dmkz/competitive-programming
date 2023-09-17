#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
int main() {
    // ускоряем ввод-вывод:
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int n; cin >> n;
    vl V(n), T(n);
    for (auto &it : V) cin >> it;
    for (auto &it : T) cin >> it;
    // предподсчитываем суффикс-суммы на векторе T:
    vl sumT(n+1);
    for (int i = n-1; i >= 0; i--)
        sumT[i] = sumT[i+1] + T[i];
    // Функция для вычисления суммы на отрезке [L, R] массива T
    auto getSumT = [&](int L, int R) { return L <= R ? sumT[L] - sumT[R+1] : 0LL; };
    // для каждого сугроба определим отрезок, в котором он будет таять
    vl full(n+1), rem(n+1);
    for (int i = 0; i < n; i++) {
        int low = i-1, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (getSumT(i, mid) > V[i]) high = mid;
            else low = mid;
        }
        // на отрезке [i, high] будет таять целиком, и остаток растает в последний день
        full[i]++;
        full[high]--;
        rem[high] += V[i] - getSumT(i, low);
    }
    // выводим ответ:
    ll countFull = 0;
    for (int i = 0; i < n; i++) {
        countFull += full[i];
        cout << countFull * T[i] + rem[i] << ' ';
    }
    cout << endl;
}

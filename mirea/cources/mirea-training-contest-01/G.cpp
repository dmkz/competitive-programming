#include <bits/stdc++.h>
using namespace std;
int64_t solve(int64_t R, const vector<int64_t> &p) {
    int64_t answ = 0;
    for (int mask = 1; mask < (1 << p.size()); mask++) {
        int64_t prod = 1;
        for (int i = 0; i < (int)p.size(); i++)
            if ((mask >> i) & 1) {
                if (prod <= R / p[i]) // проверка на переполнение
                    prod *= p[i];
                else // переполним числитель, кол-во будет нулевым
                    prod = R + 1;
            }
        if (__builtin_popcount(mask) % 2 == 1)
            answ += (R / prod);
        else
            answ -= (R / prod);
    }
    return answ;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int64_t L, R; int n;
    cin >> L >> R >> n;
    vector<int64_t> p(n);
    for (auto &it : p)
        cin >> it;
    // сортируем и удаляем повторы:
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    // решение задачи по формуле включений-исключений:
    cout << solve(R, p) - solve(L-1, p) << endl;
}

#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
int main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных
    int n; cin >> n;
    vi L(n); for (auto &it : L) cin >> it;
    // решение задачи
    int firstDead = n, answ{};
    for (int i = n-1; i >= 0; i--) {
        answ += (i < firstDead);
        remin(firstDead, i - L[i]);
    }
    cout << answ << endl;
}

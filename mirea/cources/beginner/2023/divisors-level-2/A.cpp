#include <bits/stdc++.h>
using namespace std;
int main() {
    int64_t n, k;
    cin >> n >> k;
    k--; // 0-индексация делителей
    // находим все делители числа n
    // lower: делители до корня включительно
    // upper: делители больше корня не включительно
    vector<int64_t> lower, upper;
    for (int64_t x = 1; x * x <= n; x++)
        if (int64_t y = n / x; x * y == n) {
            lower.push_back(x);
            if (y != x) upper.push_back(y);
        }
    // объединяем два списка делителей:
    while(!upper.empty()) {
        lower.push_back(upper.back());
        upper.pop_back();
    }
    // выводим ответ:
    if (k < lower.size()) cout << lower[k] << '\n';
    else cout << "-1\n";
}
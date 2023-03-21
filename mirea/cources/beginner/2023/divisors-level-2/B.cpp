#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    // будем раскладывать на минимальные простые вроде 24 = 2 * 2 * 2 * 3,
    // а потом перемножим так, чтобы их было ровно k
    vector<int> expansion;
    for (int p = 2; p * p <= n; p++)
        while (n % p == 0) {
            expansion.push_back(p);
            n /= p;
        }
    if (n > 1) // n - простое
        expansion.push_back(n);
    // умножаем с конца так, пока не останется k чисел
    while ((int)expansion.size() > k) {
        int last = expansion.back();
        expansion.pop_back();
        expansion.back() *= last;
    }
    // выводим ответ
    if ((int)expansion.size() < k) cout << "-1\n";
    else for (int x : expansion) cout << x << ' ';
}
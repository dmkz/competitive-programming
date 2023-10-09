#include <bits/stdc++.h>
using namespace std;
int main() {
    int k, sum = 0;
    cin >> k;
    for (int i = 0, a; i < k; i++) {
        cin >> a;
        sum += a;
    }
    int Min = INT_MAX, Max = INT_MIN;
    for (int n = max(3, k); n <= 1000000; n++) {
        // какая сумма должна быть?
        int need = (n-2)*180;
        // сколько остаётся набрать?
        int remSum = need - sum;
        // сколько углов у нас осталось?
        int remCnt = n - k;
        // каждый оставшийся угол от 1 до 179
        if (1 * remCnt <= remSum && remSum <= 179 * remCnt)
        {
            Min = min(Min, n);
            Max = max(Max, n);
        }
    }
    if (Min > Max)
        cout << "-1\n";
    else
        cout << Min << ' ' << Max << endl;
}

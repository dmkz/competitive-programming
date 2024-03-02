#include <bits/stdc++.h>
using namespace std;
int main() {
    int answ = 1, n;
    cin >> n;
    // каждый новый разрез пересекает все другие разрезы и края окружности
    for (int i = 1; i <= n; ++i)
        answ += i;
    cout << answ << endl;
    return 0;
}

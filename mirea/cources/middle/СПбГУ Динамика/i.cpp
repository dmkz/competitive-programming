#include <bits/stdc++.h>
using namespace std;
int main() {
    // инициализация рюкзака:
    const int SMAX = 10100;
    bitset<SMAX> dp;
    dp[0] = 1;
    // переходы:
    int s, n; cin >> s >> n;
    while (n --> 0) {
        int a; cin >> a;
        dp |= dp << a;
    }
    // нахождение ответа:
    int answ = 0;
    for (int i = 0; i <= s; i++)
        if (dp[i]) answ = i;
    cout << answ << endl;
}
#include <bits/stdc++.h>
using namespace std;
int main() {
    // нам нужно пройти слева направо, суммируя все значения "a", и узнать
    // величину максимального "проседания" по мане (минимальный баланс)
    // надо иметь на старте столько маны, чтобы этот минимум не увёл в
    // отрицательную зону
    int n; cin >> n;
    int64_t balance = 0, minBalance = 0;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        balance += a;
        if (balance < minBalance)
            minBalance = balance;
    }
    cout << -minBalance << endl;
}

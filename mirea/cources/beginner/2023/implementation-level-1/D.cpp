#include <bits/stdc++.h>
using namespace std;
int solve(int delta, int a, int b) {
    // чекаем нулевой день
    if (8 * a >= delta)
        return 0;
    if (b >= a) // никогда, т.к. сползает не дольше, чем поднимается
        return -1;
    // позиция после первого дня:
    delta -= 8 * a;
    delta += 12 * b;
    a *= 12;
    b *= 12;
    // теперь в i-й день расстояние до цели будет:
    // delta - i * (a - b) - a
    // когда станет <= 0?
    // delta - i * (a - b) - a <= 0
    // delta - a <= i * (a - b)
    // Ответ: i = ceil((delta-a)/(a-b))
    int p = delta - a;
    int q = a - b;
    return 1 + (p + q - 1) / q;
}
int main() {
    int h1, h2, a, b;
    cin >> h1 >> h2 >> a >> b;
    cout << solve(h2-h1,a,b) << '\n';
}

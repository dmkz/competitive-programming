#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }

vi getPrimeDivs(int x) {
    vi primeDivs;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            primeDivs.push_back(i);
            do { x /= i; } while (x % i == 0);
        }
    }
    if (x > 1) primeDivs.push_back(x);
    return primeDivs;
}

int main() {
    // пришли в число x
    // значит последнее выбранное p является делителем числа x
    // нам нужен максимальный простой делитель, чтобы отрезок, откуда
    // мы могли прийти, был максимально возможной длины
    int X; cin >> X;
    vi leftMost(X+1, X+10);
    for (int x = 3; x <= X; x++)
        for (int p : getPrimeDivs(x))
            remin(leftMost[x], std::max(p+1, x - p + 1));
    int answ = X;
    for (int p : getPrimeDivs(X))
        for (int i = std::max(p+1, X - p + 1); i <= X; i++)
            remin(answ, leftMost[i]);
    cout << answ << endl;
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем координаты начала и конца:
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // считаем сколько шагов должны сделать в каждом направлении
    const int dx = abs(x1-x2);
    const int dy = abs(y1-y2);
    // пока можем - шагаем по диагонали, затем ходим лишь в направлении осей
    // получаем, что min(dx, dy) шагов по диагонали
    // затем max(dx, dy) - min(dx, dy) в направлении одной оси
    // суммарно max(dx, dy)
    cout << max(dx, dy);
}
// Автор идеи: Jakos
// Автор кода: dmkozyrev
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129957434
#include <bits/stdc++.h>
using ld = long double;
// функция, которая сообщит ответ и завершает работу программы с кодом 0:
void answer(int x, int y) {
    std::cout << "! " << x << ' ' << y << std::endl;
    std::exit(0);
}
// функция, которая спрашивает вектор для точки (x,y)
auto ask(int x, int y) {
    std::cout << "? " << x << ' ' << y << std::endl;
    ld dx,dy; std::cin >> dx >> dy;
    if (dx*dx + dy*dy < 1E-9) {
        // попали в загаданную точку, нужно вывести ответ
        answer(x,y);
    }
    return std::make_pair(dx,dy);
}
void solve(int xmin, int ymin, int xmax, int ymax) {
    if (xmax == xmin && ymin == ymax) {
        // точка найдена внутри бинпоиска
        answer(xmin,ymin);
    }
    // спрашиваем центр квадрата
    const int xmid = (xmin + xmax)/2;
    const int ymid = (ymin + ymax)/2;
    auto [dx,dy] = ask(xmid,ymid);
    // самое главное: определить, в какой четверти лежит точка
    // (относительно центра квадрата)
    if (dx < 0 && dy < 0) solve(xmin,ymin,xmid-1,ymid-1);
    else if (dx > 0 && dy < 0) solve(xmid+1,ymin,xmax,ymid-1);
    else if (dx < 0 && dy > 0) solve(xmin,ymid+1,xmid-1,ymax);
    else if (dx > 0 && dy > 0) solve(xmid+1,ymid+1,xmax,ymax);
    // теперь она лежит на какой-то из осей
    else if (dx > 0) solve(xmid+1,ymid,xmax,ymid);
    else if (dx < 0) solve(xmin,ymid,xmid-1,ymid);
    else if (dy < 0) solve(xmid,ymin,xmid,ymid-1);
    else if (dy > 0) solve(xmid,ymid+1,xmid,ymax);
    else throw 1; // что-то странное и непредвиденное случилось, аварийно завершаемся
}
int main() {
    const int MAX = (int)1e9;
    const int MIN = -MAX;
    solve(MIN,MIN,MAX,MAX);
    return 0;
}
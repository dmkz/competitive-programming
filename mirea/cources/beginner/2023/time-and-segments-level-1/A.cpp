#include <bits/stdc++.h>
using namespace std;
int main() {
    // для работы с временем (чтение и вывод) удобнее всего
    // использовать scanf и printf, поддерживающие регулярные выражения
    int h, m, a;
    scanf("%d:%d %d", &h, &m, &a);
    const int currTime = h * 60 + m;
    const int nextTime = currTime + a;
    m = nextTime % 60;
    h = nextTime / 60 % 24;
    // выводим время с лидирующими нулями и ровно 2 символа:
    printf("%02d:%02d", h, m);
}
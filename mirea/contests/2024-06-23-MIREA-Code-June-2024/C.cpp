#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acos(-1.0L);
// вычисляем константу Эдуарда из первых двух примеров
// нам сказано, что многоугольник увеличивается равномерно с одной и той же скоростью
// если сейчас ребро было a, то через t секунд будет a + t * speed
// узнаем speed по примерам в условии, затем выразим t через s, a, n, speed и вычислим
ld getSpeed() {
    int n = 4, a = 2; ld s = 2; ld t = 4.379776869613;
    // s = n * a^2 / (4 * tan(pi / n)) <--- площадь правильного многоугольника
    // s = n * (a+speed*t)^2 / (4 * tan(pi / n)) <--- то же самое, но через t секунд
    // 2 = 1 + speed * t => speed = (2 - 1) / t
    ld speed = 1 / t;
    return speed;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(12);
    ld speed = getSpeed();
    int tt; cin >> tt;
    while (tt --> 0) {
        int n, a; ld s;
        cin >> n >> a >> s;
        // сначала узнаем новое ребро из формулы s = n * a^2 / (4 * tan(pi / n))
        ld a1 = sqrt(s * 4 * tan(pi / n) / n);
        // теперь поделим разницу между рёбрами на константу Эдуарда, чтобы вычислить время
        cout << (a1 - a) / speed << endl;
    }
}
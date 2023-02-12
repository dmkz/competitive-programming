#include <bits/stdc++.h>
using namespace std;
int main() {
    int64_t n; cin >> n;
    // блоки:
    // 1
    // 1 2
    // 1 2 3
    // 1 2 3 4
    // 1 ... k
    // 1 ... k k+1
    // найдём макс k такое, что n лежит внутри его блока
    // в каждом i-м блоке ровно i чисел
    // получается 1 + 2 + 3 + ... + k >= n
    // k * (k+1) / 2 >= n
    // решим квадратное уравнение (равенство)
    // надо взять положительный корень
    // k * k + k - 2 * n == 0
    // не жадничаем - используем long double для максимальной точности
    long double A = 1;
    long double B = 1;
    long double C = -2 * n;
    long double D = sqrtl(B * B - 4 * A * C);
    // sqrtl = квадратный корень в типе long double (суффикс 'l' после sqrt)
    // положительный корень:
    long double positive_root = (-B + D) / (2 * A);
    int64_t kApprox = int64_t(positive_root); 
    // получили примерный ответ, настоящий k+-1:
    for (int delta = +1; delta >= -1; delta--)
        if (int64_t k = kApprox + delta; k * (k+1)/2 < n)
        {
            cout << n - k * (k+1)/2 << endl;
            return 0;
        }
    assert(false && "Oh shit, here we go again...");
    // мы никогда не ожидаем, что попадём сюда, то есть, ответ
    // будет найден внутри тела "if". программа вылетит благодаря assert,
    // если случайно попадём сюда
}
/*
    Задача: 655. Кодирование данных
    
    Решение: расширенный алгоритм Евклида, диофантово уравнение, O(log(code))
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>

typedef long long ll;
typedef __int128_t Int;

template<typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
bool euclid(T a, T b, T c, T& x, T& y) {
// Решение диофантова уравнения a*x + b*y = c

    // Частные случаи:
    if (a < b)  { return euclid(b, a, c, y, x); }
    if (c == 0) { x = b; y = -a; return true;   }
    if (b == 0) { x = c; y =  0; return true;   }
    // Прямой ход:
    std::vector<T> r{a, b}, q;
    while (b != 0 && a % b != 0) {
        q.push_back(a / b);
        r.push_back(a % b);
        a = b;
        b = r.back();
    }
    assert(r.back() != 0);
    if (c % r.back() != 0) {
        return false;
    }
    // Обратный ход:
    x = 0, y = 1;
    while (!q.empty()) {
        auto z = -q.back() * y + x;
        x = y;
        y = z;
        q.pop_back();
    }
    x *= c / r.back();
    y *= c / r.back();
    return true;
}

int len(ll number) {
// Нахождение длины числа number в десятичной записи:
    int answ = 0;
    do answ++, number /= 10; while (number > 0);
    return answ;
}

ll solve(ll code, int k, bool less) {
// Решение задачи. Параметр less отвечает, должна ли длина искомого числа быть меньше длины кода
    int len = ::len(code) - (int)less;
    if (k == len) return code;
    // Считаем необходимые степени десятки и находим частное решение диофантова уравнения:
    ll pow1 = 1, pow2 = 1;
    for (int i = 0; i < len - k; ++i) pow1 *= 10;
    for (int i = 0; i < k; ++i) pow2 *= 10;
    Int x, y;
    auto gcd = ::gcd(pow1+1, ::gcd(pow2+1, code));
    auto dx = (pow2+1) / gcd;
    auto dy = (pow1+1) / gcd;
    if (!euclid<Int>(dy, dx, code / gcd, x, y)) {
        return code;
    }
    // Необходимо выбрать частное решение, удовлетворяющее условиям:
    // pow2 / 10 <= x + t * dx < pow2
    // 0 <= y - t * dy < pow1
    // Примерные ограничения на параметры:
    auto txmin = (pow2 / 10 - x + dx - 1) / dx;
    auto txmax = (pow2 - x) / dx;
    auto tymin = -(pow1 - y) / dy;
    auto tymax = -(-y + dy - 1) / dy;
    // Доводим примерные ограничения до точных:
    while (x + txmax * dx >= pow2) --txmax;
    while (x + (txmax+1) * dx < pow2) ++txmax;
    while (x + txmin * dx < pow2 / 10) ++txmin;
    while (x + (txmin-1) * dx >= pow2 * 10) --txmin;
    while (y - (tymin-1) * dy < pow1) --tymin;
    while (y - tymin * dy >= pow1) ++tymin;
    while (y - (tymax+1) * dy >= 0) ++tymax;
    while (y - tymax * dy < 0) --tymax;
    // Смотрим пересечение отрезков и считаем ответ:
    if (txmin > txmax) std::swap(txmin, txmax);
    if (tymin > tymax) std::swap(tymin, tymax);
    if (txmax < tymin || tymax < txmin) return code;
    auto t = std::max(tymin, txmin);
    return ll((x + t * dx)* pow1 + (y - t * dy));
}

ll get_code(ll number, int k) {
// Кодирование числа number со сдвигом k
    int len = ::len(number);
    if (len == k) return number;
    assert(len > k);
    ll pow1 = 1, pow2 = 1;
    for (int i = 0; i < len - k; ++i) pow1 *= 10;
    for (int i = 0; i < k; ++i) pow2 *= 10;
    return number + number / pow1 + number % pow1 * pow2;
}

ll solve(ll code, int k) {
    auto answ = solve(code, k, 0); // Пробуем найти число такой же длины
    if (get_code(answ, k) != code) {
        answ = solve(code, k, 1);  // Пробуем найти число длины на 1 меньше
    }
    assert(get_code(answ, k) == code);
    return answ;
}

int main() {
    ll code; int k;
    std::cin >> code >> k;
    std::cout << solve(code, k);
    return 0;
}
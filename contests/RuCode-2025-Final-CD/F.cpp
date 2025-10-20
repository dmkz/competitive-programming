// Задача: F, Вердикт: OK, Время: 0.020 сек, Память: 2 МБ

// Идея: используем теорему Пифагора и свойство делимости периметра из условия,
// чтобы для заданного a сказать, сколько уникальных прямоугольных треугольников
// существует. Из теоремы Пифагора:
// a^2 + b^2 = c^2 => a^2 = c^2 - b^2 = (c-b)*(c+b)
// получаем: a^2 = (c-b)*(c+b). Обозначим как (*)
// по условию задачи: a+b+c делится на один из катетов. Значит:
// случай 1) a+b+c делится на a;
// случай 2) a+b+c делится на b.
// Распишем каждый случай отдельно.
// Случай 1) a+b+c делится на a => b+c делится на a => b+c = k * a, k >= 1
// подставим в (*), получаем: a^2 = (c - b) * k * a => a = (c - b) * k
// получили что, (c-b) и k - парные делители числа a.
// Случай 2) a+b+c делится на b. Проблема в том, что мы не знаем b, мы знаем
// только a. Давайте выразим b через a.
// Итак, из делимости периметра на b: (a + c) = k * b
// Из теоремы Пифагора: b^2 = (c - a) * (c + a) => b = (c - a) * k
// Надо избавиться от c: c = k * b - a => b = (k * b - 2 * a) * k
// Упрощаем: b = k^2 * b - 2*k*a
// Получаем: b = (2 * k / (k^2 - 1)) * a
// Идея: НОД(2 * k, (k^2 - 1)) равен либо 1, либо 2. Тогда, после сокращения
// на НОД, знаменатель - делитель a. Снова перебираем парные делители и находим все
// возможные ответы, сортируем и удаляем повторы.
// Объединяя решения для случаев (1) и (2), получаем все возможные треугольники.

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
// Важно: нужно использовать __int128, потому что при a <= 10^{12} гипотенуза
// c прямоугольного треугольника может быть порядка 10^{24}. Иначе Wrong Answer 4
#define int __int128 
using namespace std;
// служебные функции для чтения/вывода __int128, факторизации и удаления повторов
int readInt() {
    int64_t val;
    cin >> val;
    return val;
}
void writeInt(int x) {
    cout << (int64_t)x;
}
void reunique(auto & v) {
    v.erase(unique(all(v)), v.end());
}
vector<int> factor(int n) {
    vector<int> lowerHalf, upperHalf;
    for (int x = 1; x * x <= n; x++)
        if (int y = n / x; x * y == n) {
            lowerHalf.push_back(x);
            if (x != y)
                upperHalf.push_back(y);
        }
    while (upperHalf.size()) {
        lowerHalf.push_back(upperHalf.back());
        upperHalf.pop_back();
    }
    return lowerHalf;
}
// решение задачи
int solve(int a) {
    // Решение для случая (1): находим все делители числа a и проверяем каждый
    vector<int> divs = factor(a);
    vector<tuple<int,int,int>> answer;
    auto checkAndUpdate = [&](int b, int c) {
        if (b >= 1 && c >= 1 && c * c == b * b + a * a)
            answer.emplace_back(a,b,c);
    };
    for (int k : divs) {
        // c - b = a / k;
        // c + b = k * a
        int q = a / k;
        int c = (k * a + q) / 2;
        int b = c - q;
        checkAndUpdate(b, c);
    }
    // решаем для случая (2)
    for (int d : divs) {
        {
            // k - нечётное, k = 2 * t - 1. НОД(2 * k, (k^2 - 1)) = 2
            // 2t(t-1) = d <- зафиксированный делитель a
            // 2 * t^2 - 2 * t - d = 0
            // Дискриминант: D = B^2 - 4*A*C
            int D = 4 + 4 * 2 * d;
            int sqrtD = (int)sqrtl(D);
            int t1 = (2 + sqrtD) / 4;
            int t2 = (2 - sqrtD) / 4;
            for (int t : {t1, t2}) {
                int k = 2 * t - 1;
                int b = k * a / d;
                int c = k * b - a;
                checkAndUpdate(b, c);
            }
        }
        {
            // k - чётное, k = 2 * t
            // 4 * t^2 - 1 = d
            // t = sqrt((d + 1) / 4)
            int t = (int)sqrtl((d+1)/4);
            int k = 2 * t;
            int b = 2 * k * a / d;
            int c = k * b - a;
            checkAndUpdate(b, c);
        }
    }
    // сортировка троек (a, b, c) и удаление повторяющихся
    for (auto &[x, y, z] : answer) {
        if (x > y)
            swap(x, y);
        assert(x <= y && y <= z);
    }
    sort(all(answer));
    answer.erase(unique(all(answer)), answer.end());
    // вернём ответ:
    return isz(answer);
}
main() {
    int a = readInt();
    writeInt(solve(a));
    cout << endl;
}

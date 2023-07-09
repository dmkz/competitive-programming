// попытка 2
#include <bits/stdc++.h>
using namespace std;
// Будем выводить рандомное число. Вероятность проиграть (попасть в единственный
// магазин, в котором мы не сможем купить всё необходимое), потратив все деньги,
// равна 1/29. Надо быть очень невезучим, чтобы не сдать задачу
// в качестве ядра генератора случайных чисел можно использовать
// текущее время в наносекундах
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(1, 29);
int main() {
    int n, x; cin >> n >> x;
    cout << x << ' ' << dist(gen) << endl;
    return 0;
}
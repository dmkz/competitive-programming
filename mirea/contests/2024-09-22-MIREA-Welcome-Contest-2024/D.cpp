#include <bits/stdc++.h>
using namespace std;
/*
    Тот, кто оказался в полном квадрате, проиграл, потому что на любой его ход, выводящий
    из состояния полного квадрата, мы можем сделать его же ход и снова получить квадрат:
    если он уменьшает степень вхождения простых, которая была чётной, делая её нечётной,
    то мы уменьшаем её ещё раз, возвращая чётность, пока не придём в единицу
    (все простые в нулевой степени):
    1 = 2^0 * 3^0 * 5^0 * ...
    
    Поэтому, достаточно проверить, что все простые входят в разложение в чётной степени.
    Это условие того, что число является полным квадратом, поэтому можно проверить его
*/
bool isSquare(long long x) {
    long long root = (long long) sqrt((long double)(x));
    return root * root == x;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // решение задачи:
    int tt; cin >> tt;
    while (tt --> 0) {
        long long x; cin >> x;
        cout << (isSquare(x) ? "Vlad" : "Danila") << "\n";
    }
}
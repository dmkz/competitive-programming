#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // сложим все числа в словать (число, его количество)
    int n; cin >> n;
    vector<int> a(n);
    map<int,int> count;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        count[a[i]]++;
    }
    // для минимального должна быть пара и она больше него
    // если пары нет, то придётся удалить, и перейти к следующему числу
    // проверяем, есть ли пара, следующим образом: переберём степень
    // двойки (их 30 вариантов) и найдём нужный элемент поиском в словаре
    int needRemove = 0;
    for (int i = 0; i < n; i++) {
        bool pairExists = false;
        for (int d = 0; !pairExists && d <= 30; d++) {
            int powerOf2 = (1 << d); // степень двойки: 2^d
            int wantToFind = (powerOf2 - a[i]); // ищем a[j] = 2^d - a[i]
            if (count.count(wantToFind) > 0) { // если найден
                int cntPairs = count[wantToFind]; // сколько его
                assert(cntPairs >= 1); // если мы нашли элемент, то его точно >= 1
                // могло так оказаться, что a[j] == a[i] и его одна штука
                // то есть мы нашли сам i-й элемент и не можем включить его в пару
                if (cntPairs > 1 || wantToFind != a[i])
                    pairExists = true;
            }
        }
        if (!pairExists)
            needRemove++;
    }
    cout << needRemove << endl;
    return 0;
}
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // инициализация всего и вся:
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    std::vector<int> a(nRows*nCols + (1 << 20)); // значение в ячейке
    auto value = a; // ксор соседей + сама ячейка
    auto withoutLeft = value; // ксор соседей без левого + сама ячейка
    auto withoutRight = value;// ксор соседей без правого + сама ячейка
    std::vector<ll> total(nCols); // сумма ксоров в столбце
    auto columnWithoutLeft = total; // сумма ксоров без левого соседа в столбце
    auto columnWithoutRight = total;// сумма ксоров без правого соседа в столбце
    int last = isz(a)-1; // последняя свободная клетка
    ll sumTotals{}; // сумма всех столбцов со всеми соседями
    // обновление суммы в столбце (со всеми связями):
    auto updateTotal = [&](int i, int x) {
        sumTotals -= total[i%nCols];
        total[i%nCols] -= value[i];
        value[i] ^= x;
        total[i%nCols] += value[i];
        sumTotals += total[i%nCols];
    };
    // обновление суммы в столбце (без левой связи):
    auto updateWithoutLeft = [&](int i, int x) {
        columnWithoutLeft[i%nCols] -= withoutLeft[i];
        withoutLeft[i] ^= x;
        columnWithoutLeft[i%nCols] += withoutLeft[i];
    };
    // обновление суммы в столбце (без правой связи):
    auto updateWithoutRight = [&](int j, int x) {
        columnWithoutRight[j%nCols] -= withoutRight[j];
        withoutRight[j] ^= x;
        columnWithoutRight[j%nCols] += withoutRight[j];
    };
    // добавить ребро i <-> j (слева направо):
    auto connectRight = [&](int i, int j) {
        if (j >= isz(a)) return;
        updateTotal(i, a[j]);
        updateWithoutLeft(i, a[j]);
        updateTotal(j, a[i]);
        updateWithoutRight(j, a[i]);        
    };
    // добавить ребро i <-> j (сверху вниз):
    auto connectDown = [&](int i, int j) {
        if (j >= isz(a)) return;
        updateTotal(i, a[j]);
        updateWithoutLeft(i, a[j]);
        updateWithoutRight(i, a[j]);
        updateTotal(j, a[i]);
        updateWithoutRight(j, a[i]);
        updateWithoutLeft(j, a[i]);
    };
    // обновить само значение в ячейке:
    auto updateValue = [&](int i, int x) {
        a[last] = x;
        updateTotal(i, x);
        updateWithoutLeft(i, x);
        updateWithoutRight(i, x);
    };
    // добавить число в начало таблицы:
    auto add = [&](int x) {
        updateValue(last,x);
        connectRight(last,last+1);
        connectDown(last,last+nCols);
        last--;
    };
    // получение ответа: сумма по столбцам, вычитая крайние столбцы (вычитая связи влево/вправо):
    auto answer = [&](){
        return sumTotals - total[(last+1)%nCols] + columnWithoutLeft[(last+1)%nCols]
                         - total[(last+0)%nCols] + columnWithoutRight[(last+0)%nCols];
    };
    { // читаем изначальные числа и заполняем ими таблицу:
        std::vector<int> input(nRows*nCols);
        for (auto &it : input) std::cin >> it;
        std::reverse(all(input));
        for (auto x : input) add(x);
    }
    // отвечаем на запросы:
    std::cout << answer() << '\n';
    int q; std::cin >> q;
    while (q --> 0) {
        int x; std::cin >> x;
        add(x);
        std::cout << answer() << '\n';
    }
}

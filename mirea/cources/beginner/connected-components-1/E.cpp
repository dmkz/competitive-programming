#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем входные данные
    int nRows, nCols, k;
    cin >> nRows >> nCols >> k;
    // читаем поле из символов, но делая границу из воды по краям
    vector a(1+nRows+1, string(1+nCols+1, '.'));
    for (int r = 1; r <= nRows; r++)
        for (int c = 1; c <= nCols; c++)
            cin >> a[r][c];
    // нужно найти компоненты связности, включая компоненту для океана
    // можем использовать поиск в глубину (для разнообразия)
    // компонента для океана будет самой первой, так как мы запускаемся
    // из клетки, лежащей за пределами поля
    vector used(1+nRows+1, vector(1+nCols+1, false));
    vector<vector<pair<int,int>>> components; // компоненты
    for (int sr = 0; sr < nRows+2; sr++)
        for (int sc = 0; sc < nCols+2; sc++)
            if (!used[sr][sc]) {
                vector<pair<int,int>> currComp; // текущая компонента
                // функция для обхода графа в глубину:
                function<void(int,int)> dfs = [&](int r, int c) {
                    // условия выхода из рекурсии:
                    if (r < 0 || r >= nRows+2) return; // вышли за пределы поля
                    if (c < 0 || c >= nCols+2) return; // вышли за пределы поля
                    if (used[r][c]) return; // клетка уже посещена
                    if (a[r][c] == '*') return; // вышли на сушу
                    // обрабатываем текущую клетку
                    used[r][c] = 1;
                    currComp.emplace_back(r, c);
                    // посещаем её соседей
                    dfs(r-1, c);
                    dfs(r+1, c);
                    dfs(r, c-1);
                    dfs(r, c+1);
                };
                dfs(sr, sc); // запускаем поиск в глубину из стартовой клетки
                components.push_back(currComp); // добавляем текущую компоненту
            }
    // теперь нужно ответить на задачу
    // нужно удалить компоненту с морем
    components.erase(components.begin());
    // затем нужно оставить k максимальных компонент
    // сортируем компоненты по убыванию размеров
    stable_sort(all(components), [](const auto &a, const auto &b){
        return a.size() > b.size();
    });
    // удаляем компоненты с конца
    int numRemoved = 0;
    while (isz(components) > k) {
        for (const auto &[r, c] : components.back()) {
            a[r][c] = '*';
            numRemoved++;
        }
        components.pop_back();
    }
    // выводим ответ:
    cout << numRemoved << '\n';
    for (int r = 1; r <= nRows; r++) {
        for (int c = 1; c <= nCols; c++)
            std::cout << a[r][c];
        std::cout << '\n';
    }
}

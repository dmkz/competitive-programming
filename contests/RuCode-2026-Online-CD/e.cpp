// геометрия, монотонный стек, O(n log(n))
// Задача: E, Вердикт: OK, Время: 0.534 сек, Память: 30 МБ
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
// точки {x, y, id}:
using tiii = std::tuple<int,int,int>;
main() {
    // читаем точки, запоминая их номер:
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<tiii> p(n);
    for (int i = 0; i < n; i++) {
        auto &[x,y,id] = p[i];
        std::cin >> x;
        id = i;
    }
    for (auto &[x,y,id] : p)
        std::cin >> y;
    // сортируем точки:
    std::sort(all(p));
    // находим ближайший >= слева монотонным стеком:
    std::vector<int> left(n);
    const int inf = (int)1e9+7;
    using pii = std::pair<int,int>;
    std::vector<pii> stack(1, pii{inf, -1});
    for (int i = 0; i < n; i++) {
        // выталкиваем меньшие элементы новым:
        const auto &[xi, yi, idI] = p[i];
        while (stack.back().first < yi)
            stack.pop_back();
        // запоминаем индекс элемента, которого не удалось вытолкнуть:
        left[i] = stack.back().second;
        // кладём новый элемент в стек:
        stack.emplace_back(yi, i);
    }
    // находим ближайший >= справа снова монотонным стеком:
    std::vector<int> right(n);
    stack = {pii{inf, -1}};
    for (int i = n-1; i >= 0; i--) {
        // выталкиваем меньшие элементы новым:
        const auto &[xi, yi, idI] = p[i];
        while (stack.back().first < yi)
            stack.pop_back();
        // запоминаем индекс элемента, которого не удалось вытолкнуть:
        right[i] = stack.back().second;
        // кладём новый элемент в стек:
        stack.emplace_back(yi, i);
    }
    // теперь считаем ответ:
    std::vector<int> answer(n);
    for (int i = n-1; i >= 0; i--) {
        const auto &[xi, yi, idI] = p[i];
        if (left[i] == -1) {
            if (right[i] == -1) {
                answer[idI] = -1;
            } else {
                // справа что-то есть:
                const auto &[xr, yr, idR] = p[right[i]];
                int distR = (xr - xi) - (yr - yi);
                answer[idI] = distR;
            }
        } else {
            if (right[i] == -1) {
                // слева что-то есть
                const auto &[xl, yl, idL] = p[left[i]];
                int distL = (xi - xl) - (yl - yi);
                answer[idI] = distL;
            } else {
                // границы есть в обоих направлениях
                // считаем справа:
                const auto &[xr, yr, idR] = p[right[i]];
                int distR = (xr - xi) - (yr - yi);
                // считаем слева:
                const auto &[xl, yl, idL] = p[left[i]];
                int distL = (xi - xl) - (yl - yi);
                // берём минимум:
                answer[idI] = std::min(distL, distR);
            }
        }
    }
    // выводим ответы:
    for (int i = 0; i < n; i++)
        std::cout << answer[i] << ' ';
    std::cout << std::endl;
}

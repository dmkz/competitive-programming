// сортировки, сканирующая прямая, обработка событий, мультисет
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using tiii = std::tuple<int,int,int>;
void solve() {
// Каждый слой нам даст k[i]+1 отрезков. i-й отрезок: первые i дверей сдвигаем влево,
// остальные двери сдвигаем вправо до упора.
// Пусть мы нашли ответ. Тогда его левая граница совпадает с каким-нибудь отрезком.
// Поэтому мы можем сразу искать ответ в таком виде. Итого:
// Для каждой левой границы мы находим максимальный возможный пустой отрезок справа
// Делаем это при помощи сканирующей прямой и обработки событий
// Мы должны пересечь n слоёв, поэтому среди всех ещё открытых отрезков (они включают)
// нашу левую границу, мы выбираем минимальную правую границу. Это и будет
// пересечением n отрезков. Для быстрого выбора минимума нам понадобится мультисет.
// В нём мы будем для каждого слоя хранить самую правую границу среди открытых
// на этом слое отрезков. Итого решение O(n log(n)), где n - число отрезков.
    
    // читаем отрезки и готовим их к сканирующей прямой:
    int n; std::cin >> n;
    vi segL(1, 0), segR(1, 0);
    int segmentId = 0;
    std::vector<tiii> events;
    auto prepareSegment = [&](int l, int r, int layerId) {
        segmentId++;
        segL.push_back(l);
        segR.push_back(r);
        events.push_back({  l, +segmentId, layerId});
        events.push_back({r+1, -segmentId, layerId});
    };
    for (int layerId = 0; layerId < n; layerId++) {
        int k, l, r; std::cin >> k >> l >> r;
        int sumRight = 0, sumLeft = 0;
        vi a(k);
        for (int i = 0; i < k; i++) {
            std::cin >> a[i];
            sumRight += a[i];
        }
        prepareSegment(l, r - sumRight, layerId);
        for (int i = 0; i < k; i++) {
            sumLeft += a[i];
            sumRight -= a[i];
            prepareSegment(l + sumLeft, r - sumRight, layerId);
        }
    }
    // сортировка событий:
    std::sort(all(events));
    // сканирующая прямая:
    std::multiset<int> openedLayerSegments;
    vi itemInSet(n, -1);
    // вставка отрезка:
    auto insertSegment = [&](int id, int layer) {
        // этот отрезок становится новым максимумом для соответствующего слоя
        int right = segR[id];
        if (itemInSet[layer] != -1) {
            auto iter = openedLayerSegments.find(itemInSet[layer]);
            openedLayerSegments.erase(iter);
        }
        itemInSet[layer] = right;
        openedLayerSegments.insert(right);
    };
    // удаление отрезка:
    auto removeSegment = [&](int id, int layer) {
        int right = segR[id];
        if (itemInSet[layer] == right) {
            auto iter = openedLayerSegments.find(itemInSet[layer]);
            openedLayerSegments.erase(iter);
            itemInSet[layer] = -1;
        }
    };
    int answ = 0;
    for (const auto &[x, id, layer] : events) {
        if (id > 0) {
            // отрезок добавляется
            insertSegment(+id, layer);
            // если все слои открыты, обновляем ответ:
            if (isz(openedLayerSegments) == n)
                answ = std::max(answ, *openedLayerSegments.begin() - x);
        } else {
            assert(id < 0);
            // отрезок удаляется
            removeSegment(-id, layer);
        }
    }
    std::cout << answ << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; // std::cin >> tt;
    while (tt --> 0) solve();
}

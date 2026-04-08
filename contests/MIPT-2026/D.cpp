// конструктив, отрезки на прямой, сортировка отрезков
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем отрезки на числовой прямой
    // на отрезки слева-направо забиваем: их обработаем автоматически,
    // перемещаясь из 0 в m. Остальные отрезки (справа-налево) нужно
    // обработать оптимально, так как мы будем возвращаться. По каждому
    // такому отрезку мы пройдём минимум три раза.
    int n, m; cin >> n >> m;
    vector<pair<int,int>> segs;
    for (int i = 0; i < n; i++) {
        int s, t; cin >> s >> t;
        if (s > t)
            segs.emplace_back(t, s);
    }
    sort(segs.begin(), segs.end());
    // нужно достигнуть минимум, поэтому разбиваем отрезки на группы
    // из последовательно пересекающихся. К ответу прибавляется длина
    // каждой такой группы
    int64_t answ = m;
    for (int i = 0, j; i < isz(segs); i = j) {
        int maxR = segs[i].second;
        for (j = i; j < isz(segs) && segs[j].first <= maxR; j++)
            maxR = max(maxR, segs[j].second);
        // [i, j) -- группа последовательно пересекающися отрезков
        // начало группы: segs[i].first, конец: maxR
        answ += (maxR - segs[i].first) * 2;
    }
    cout << answ << endl;
}

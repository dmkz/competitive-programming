#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using pii = pair<int,int>;
using ll = long long;
void solve() {
    int nRows, nCols, q;
    cin >> nRows >> nCols >> q;
    // посчитаем для каждой площади сколько таких матриц есть
    vector<int> cnt(nRows * nCols + 1);
    for (int h = 1; h <= nRows; h++)
        for (int w = 1; w <= nCols; w++)
            cnt[h * w] += (nRows - h + 1) * (nCols - w + 1);
    // посчитаем суффикс-суммы для этого количества, чтобы быстро искать нужную
    // площадь бинарным поиском по суффикс суммами
    vector<ll> sum(nRows * nCols + 1);
    sum.back() = cnt.back();
    for (int i = isz(sum)-2; i >= 0; i--)
        sum[i] = cnt[i] + sum[i+1];
    // напишем функцию, которая ищет нам хотя бы площадь:
    auto query = [&](ll id) -> pii {
        int low = -1, high = isz(sum);
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (sum[mid] > id)
                low = mid;
            else
                high = mid;
        }
        // ответ в low. Находим номер в текущей группе
        if (high < isz(sum))
            id -= sum[high];
        // теперь нужно найти высоту матрицы - делитель площади
        // перебираем все делители в порядке убывания
        for (int h = nRows; h >= 1; h--)
            if (int w = low / h; w <= nCols && w * h == low) {
                // кол-во матриц с текущей высотой h и ширинов w
                int currCnt = (nRows - h + 1) * (nCols - w + 1);
                // определяем эта матрица нам нужна или не эта
                if (id < currCnt)
                    return {h * w, h};
                else // не эта, идём дальше
                    id -= currCnt;
            }
        assert(false);
        return {-1, -1};
    };
    // читаем запросы и отвечаем на них
    while (q --> 0) {
        ll id; cin >> id;
        id--;
        auto [s, r] = query(id);
        cout << s << ' ' << r << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        solve();
    }
}
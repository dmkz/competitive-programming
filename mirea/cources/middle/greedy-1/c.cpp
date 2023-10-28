#include <bits/stdc++.h>
#define rall(x) (x).rbegin(), (x).rend()
void setmin(auto &x, const auto &y) { if (x > y) x = y; }
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // используем тот факт, что нам нужно купить ВСЕ товары
    // тогда чем чаще мы будем использовать скидку, тем лучше
    // поэтому нам нужна лишь минимальная скидка
    // набирать товары будем в порядке убывания, а потом
    // использовать скидку
    int minSale = (int)1e9+1;
    {
        int m; cin >> m;
        for (int i = 0; i < m; ++i) {
            int v; cin >> v; 
            setmin(minSale, v);
        }
    }
    // читаем товары + сортируем в порядке убывания:
    int n; cin >> n;
    vector<int> items(n);
    for (auto& it : items)
        cin >> it;
    sort(rall(items));
    // набираем товары
    int currPos = 0, sum = 0;
    while (currPos < n) {
        int saleEnd = min(currPos+minSale,n);
        // честно набираем минимальное необходимое кол-во товаров
        while (currPos < saleEnd)
            sum += items[currPos++];
        // остальные 2 получаем бесплатно и двигаемся вперёд
        currPos = min(currPos+2, n);
    }
    cout << sum << endl;
}

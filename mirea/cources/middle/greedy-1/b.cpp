#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, h; cin >> n >> h;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // найдём оптимальное k бинарным поиском по ответу
    // пусть мы зафиксировали в бинпоиске что хотим поставить
    // k бутылок. Будем их ставить в порядке убывания высот
    // тогда в ответ пойдёт каждая нечётная бутылка
    int low = -1, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        // проверяем можно ли поставить "mid" бутылок
        vector<int> b(a.begin(), a.begin()+mid);
        sort(all(b), greater<>());
        int emptyHeight = h;
        bool ok = 1;
        for (int i = 0; i < mid; i += 2) {
            emptyHeight -= b[i];
            if (emptyHeight < 0) {
                ok = false;
                break;
            }
        }
        if (ok) low = mid;
        else high = mid;
    }
    cout << low << endl;
}

#include <bits/stdc++.h>
using namespace std;
// будем честно считать, кто выиграет
const vector<vector<int>> steps{{2,5,13},{3,7,11}};
bool isWin(int who, int n) {
// сейчас очередь хода `who` и на столе `n` печенек
// сначала смотрим, считали ли мы уже такое состояние:
    static map<pair<int,int>, bool> cache;
    if (auto it = cache.find({who,n}); it != cache.end())
        return it->second; // возвращаем посчитанный ответ
// иначе нужно честно посчитать ответ
    bool result = false; // поражение по дефолту
// ищем победный ход:
    for (int s : steps[who])
        if (s <= n && !isWin(1-who,n-s))
            result = true; // нашли такой ход, что оппонент проиграет
// возвращаем посчитанный ответ, кешируя его:
    return cache[{who,n}] = result;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        cout << (isWin(0,n) ? "Stepan" : "Andrey") << '\n';
    }
}
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void play(auto result) {
// играем один раунд против жюри
// спрашиваем задаче в порядке убывания баллов за них
// максимальная попытка, которая выжила, идёт в ответ
    for (auto [score, id] : result) {
        cout << "retest " << id << endl;
        int res; cin >> res;
        if (res == 1) {
            break;
        }
    }
    cout << "done" << endl;
}
int main() {
    int n; cin >> n;
    vector<pair<int,int>> result; // пары (значение, номер задачи) -> посорчены
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        if (p != 0)
            result.emplace_back(p, i);
    }
    sort(all(result), greater<>());
    // начинаем играть
    int t; cin >> t;
    while (t --> 0) play(result);
}

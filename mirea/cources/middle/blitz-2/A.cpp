#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // параллелограмм -- фигура, у которой противоположные стороны равны
    // то есть, либо это две равные палочки + другие две равные палочки
    // либо это 4 равные палочки
    // сначала набираем по 4 равные палочки, потом набираем по группе из 2-х по 2
    int n; cin >> n;
    vector<int> cnt(200001);
    // для каждой длины палочки считаем количество параллелограммов:
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        cnt[a]++;
    }
    // набираем четвёрки по максимуму:
    int answ{};
    for (int len = 1; len <= 200000; len++) {
        while (cnt[len] >= 4) {
            answ++;
            cnt[len] -= 4;
        }
    }
    // теперь набираем двойки
    // для этого надо посчитать сколько осталось палочек с количеством >= 2
    int n2{};
    for (int len = 1; len <= 200000; len++)
        n2 += (cnt[len] >= 2);
    // прибавляем к ответу двойки (две палочки мы берём в группу с другими двумя палочками):
    answ += n2 / 2;
    cout << answ << endl;
}
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; cin >> n >> k;
    // храним номера живых людей в векторе
    vector<int> players;
    for (int i = 1; i <= n; i++)
        players.push_back(i);
    int pos = 0; // позиция ведущего
    while (k --> 0) {
        // читаем сколько надо отсчитать
        int step; cin >> step;
        // отсчитываем от текущей позиции
        (pos += step) %= (int)players.size();
        // выводим выбывшего
        cout << players[pos] << ' ';
        // удаляем его из вектора
        players.erase(players.begin()+pos);
    }
}

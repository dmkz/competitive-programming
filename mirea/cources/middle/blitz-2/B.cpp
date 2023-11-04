#include <bits/stdc++.h>
using namespace std;
int main() {
    // это задача на периодичность
    // (1 + 2 + 3 + 4 + ... + n) % p имеет период до 2*p
    // надо промоделировать процесс, отмечая посещённые точки
    int64_t p, n; cin >> p >> n;
    int curr = 0;
    vector<bool> visited(p);
    visited[curr] = 1;
    // моделируем процесс, шагая вперёд по окружности:
    for (int step = 1; step <= min(2*p, n); step++) {
        curr = (curr + step) % p;
        visited[curr] = 1;
    }
    // считаем ответ, проделав все шаги:
    int answ = 0;
    for (int i = 0; i < p; i++)
        answ += visited[i];
    cout << answ << endl;
}

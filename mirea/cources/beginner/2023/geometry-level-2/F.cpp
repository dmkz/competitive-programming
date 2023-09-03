#include <bits/stdc++.h>
using namespace std;
int main() {
    // ответ равен либо 2, либо 3
    // понадобятся два вектора, если все точки лежат на одной и той же прямой
    // иначе понадобится ровно три вектора
    
    // чтение:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // подсчёт: считаем число различных векторов между всеми парами точек
    set<pair<int,int>> vectors;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j) {
                // нам нужен вектор {dx / gcd(dx, dy), dy / gcd(dx, dy)}
                int dx = x[j] - x[i];
                int dy = y[j] - y[i];
                int g = gcd(abs(dx), abs(dy));
                vectors.insert({dx / g, dy / g});
            }
    // либо 2, либо 3:
    cout << (vectors.size() == 2u ? 2 : 3) << std::endl;
}

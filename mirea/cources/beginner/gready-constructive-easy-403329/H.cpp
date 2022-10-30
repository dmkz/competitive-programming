#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // текущий размер S - это сумма всех a[i]
    // когда мы сжимаем одну песню, то размер уменьшается на:
    //     delta[i] = a[i] - b[i]
    // выгодно выполнять сжатия песен с максимальным delta[i]
    
    // читаем данные, считаем текущий размер и сохраняем дельты
    int n, requiredSize;
    cin >> n >> requiredSize;
    int64_t givenSize = 0;
    vector<int> delta(n);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        delta[i] = (a - b);
        givenSize += a;
    }
    // сортируем дельты по убыванию
    sort(delta.begin(), delta.end(), greater<>());
    // сжимаем пока не сжалось
    int completedCompressions = 0;
    while (givenSize > requiredSize && completedCompressions < n) {
        givenSize -= delta[completedCompressions];
        completedCompressions++;
    }
    // если не достигли требуемого размера, то ответ -1:
    if (givenSize > requiredSize)
        completedCompressions = -1;
    cout << completedCompressions << endl;
    return 0;
}
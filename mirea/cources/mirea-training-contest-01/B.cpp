#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    map<int, int> cntForX, cntForY;
    map<pair<int,int>, int> cntForXY;
    int64_t answ{};
    for (int i = 0; i < n; i++) {
        // читаем точку:
        int x, y; cin >> x >> y;
        // считаем, сколько точек мы можем выбрать в пару
        // к прочитанной, так, чтобы либо x, либо y совпали
        answ += cntForX[x] + cntForY[y] - cntForXY[{x,y}];
        // добавляем нашу точку:
        cntForX[x] += 1;
        cntForY[y] += 1;
        cntForXY[{x,y}] += 1;
    }
    cout << answ << endl;
}

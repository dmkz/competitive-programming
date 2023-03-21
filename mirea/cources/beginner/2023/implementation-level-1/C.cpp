#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector bus(n, vector(4, 0));
    // bus[i][j] = кто сидит на i-м ряду на j-м месте
    // 0 = слева у окна
    // 1 = слева не у окна
    // 2 = справа не у окна
    // 3 = справа у окна
    
    // сажаем
    for (int i = 0; i < m; i++) {
        if (i < 2 * n) { // у окна
            bus[i/2][(i%2)*3] = i+1;
        } else { // не у окна
            bus[(i-2*n)/2][(i%2)+1] = i+1;
        }
    }
    
    // выходим
    for (int i = 0; i < n; i++) {
        for (int j : {1,0,2,3}) {
            int id = bus[i][j];
            // если там кто-то сидит, то он выходит
            if (id) cout << id << ' ';
        }
    }
}

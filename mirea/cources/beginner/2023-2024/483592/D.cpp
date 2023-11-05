#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // считаем максимальное количество шоколадок, которое у нас есть:
    int n; cin >> n;
    int max = 0;
    vector<int> cnt(1e6+1);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        cnt[x]++;
        if (cnt[x] > cnt[max])
            max = x;
    }
    // теперь воспользуемся формулой. Ответ почти всегда равен n, кроме одного случая
    // когда у нас число максимумов больше (n+1)/2
    // x_x_x_x_x_xxxxxx
    int maxCnt = cnt[max];   // количество максимумов
    int remCnt = n - maxCnt; // количество всех остальных
    int answ = n; // почти всегда n
    if (maxCnt > remCnt+1)
        // единственный случай, когда не сможем добиться ответа равного n
        answ = remCnt * 2 + 1;
    cout << answ << endl;
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n)
    {
        // рещаем задачу
        vector<int> a(n+1);
        for (int i = 0; i < n; i++) {
            int L; cin >> L;
            // прибавляем на отрезке [i-L, i-1]
            int left = max(i - L, 0);
            int right = i-1;
            if (left <= right) {
                a[left]++;
                a[right+1]--;
            }
        }
        // считаем все прибавления
        vector<int> b(n+1);
        for (int i = 0; i <= n; i++) {
            b[i] = (i-1 >= 0 ? b[i-1] : 0) + a[i];
        }
        // считаем ответ - количество живых, b[i] == 0
        int answ = 0;
        for (int i = 0; i < n; i++) {
            answ += (b[i] == 0);
        }
        cout << answ << endl;
    }
}
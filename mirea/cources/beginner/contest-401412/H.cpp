#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходные данные:
    int n, nQueries;
    cin >> n >> nQueries;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем две величины:
    // maxIncRight[i] = длина максимального неубывания вправо a[i] <= a[i+1] <= ...
    // maxDecLeft[i] = длина максимального неубывания влево a[i] <= a[i-1] <= ...
    // тогда [L, R] - лесенка, если: maxIncRight[L] + maxDecLeft[R] >= R - L + 1
    vector<int> maxIncRight(n, 1);
    for (int i = n-2; i >= 0; i--)
        if (a[i] <= a[i+1])
            maxIncRight[i] = maxIncRight[i+1] + 1;
    
    vector<int> maxDecLeft(n, 1);
    for (int i = 1; i < n; i++)
        if (a[i-1] >= a[i])
            maxDecLeft[i] = maxDecLeft[i-1] + 1;
    // теперь готовы отвечать на запросы
    while (nQueries --> 0) {
        int L, R; cin >> L >> R;
        L--, R--; // переходим к 0-индексации
        if (maxIncRight[L] + maxDecLeft[R] >= R - L + 1)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // читаем длину строки и саму строку:
    int n; cin >> n;
    string s; cin >> s;
    // заменяем буквы их номерами в алфавите:
    for (auto &it : s)
        it -= 'a';
    // считаем количество каждой буквы:
    vector<int> countRight(26);
    vector<int> countLeft(26);
    for (auto it : s)
        countRight[it]++;
    // считаем ответ:
    int answ = 0;
    for (int i = 0; i < n; i++) {
        // символы [0, ..., i] отнесём к левой части
        // символы [i+1, ..., n-1] - к правой части
        countRight[s[i]]--;
        countLeft[s[i]]++;
        // считаем ответ для текущего разделения:
        int fL = 0, fR = 0;
        for (int j = 0; j < 26; j++) {
            fL += (countLeft[j] > 0);
            fR += (countRight[j] > 0);
        }
        // обновляем ответ:
        answ = max(answ, fL + fR);
    }
    cout << answ << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0)
        solve();
}

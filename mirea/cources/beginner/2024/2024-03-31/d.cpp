#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // посчитаем количество слов и сами слова:
    int n; cin >> n;
    vector<string> words(n);
    map<string, int> count;
    for (auto &word : words) {
        cin >> word;
        count[word]++;
    }
    // переберём каждое слово и попробуем его разрезать на две половины
    // семью различными способами. проверим, есть ли эти половины в наборе
    string answer(n, '0');
    for (int wordIndex = 0; const auto &word : words) {
        for (int i = 1; i < (int)word.size(); i++) {
            // левая половина: [0, ..., i-1]
            // правая половина: [i, ..., n-1]
            string left = word.substr(0, i);
            string right = word.substr(i);
            // если они есть в наборе, то увеличиваем ответ:
            if ((count[left] > 0) && (count[right] > 0)) {
                answer[wordIndex]++;
                break;
            }
        }
        wordIndex++;
    }
    // выводим ответ:
    cout << answer << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0)
        solve();
}

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // читаем кол-во слов:
    int n; cin >> n;
    // читаем данные и считаем сколько раз было названо каждое слово
    // countWord[s] = кол-во раз, сколько было названо слово s
    map<string, int> countWord;
    // words[i] = список из названных слов i-м человеком
    vector<vector<string>> words(3);
    for (int id = 0; id < 3; id++) {
        words[id].resize(n);
        for (auto &word : words[id]) {
            cin >> word;
            countWord[word]++;
        }
    }
    // считаем очки каждого:
    vector<int> score(3);
    for (int id = 0; id < 3; id++) {
        for (auto &word : words[id]) {
            if (countWord[word] == 1) {
                score[id] += 3;
            } else if (countWord[word] == 2) {
                score[id] += 1;
            }
        }
    }
    // выводим очки:
    for (int id = 0; id < 3; id++)
        cout << score[id] << ' ';
    cout << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0)
        solve();
}

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // в этой задаче нам надо знать только количество каждой буквы в каждой строке
    vector<int64_t> countLettersInFirst(26);
    vector<int64_t> countLettersInSecond(26);
    // обе строки изначально равны "a" по условию задачи (первый абзац текста)
    countLettersInFirst[0] = 1;
    countLettersInSecond[0] = 1;
    // читаем запросы и отвечаем на них:
    int q; cin >> q;
    while (q --> 0) {
        // читаем текущий запрос
        int id, k; string x;
        cin >> id >> k >> x;
        // считаем число каждой буквы в строке x
        vector<int64_t> countX(26);
        for (auto it : x)
            countX[it - 'a']++;
        // прибавляем к нужной строке, умножая при этом на k:
        if (id == 1) {
            for (int i = 0; i < 26; i++)
                countLettersInFirst[i] += k * countX[i];
        } else {
            for (int i = 0; i < 26; i++)
                countLettersInSecond[i] += k * countX[i];
        }
        // сравниваем две строки:
        // если в S есть некоторая буква x, которая меньше некоторой буквы y в T,
        // то мы на первое место можем поставить эти буквы, а остальное нас не волнует
        // это первый случай
        bool ok = false;
        for (int i = 0; i < 26; i++)
            for (int j = i + 1; j < 26; j++)
                if (countLettersInFirst[i] > 0 && countLettersInSecond[j] > 0) {
                    ok = true;
                }
        // второй случай: если s пустая, то ответ всегда yes
        int64_t lengthS = 0;
        for (int i = 0; i < 26; i++)
            lengthS += countLettersInFirst[i];
        if (lengthS == 0) {
            ok = true;
        }
        // третий случай: если есть ровно одна уникальная буква и в S, и в T,
        // то ответ yes, если они совпадают и в S этой буквы меньше
        int countUniqS = 0, countUniqT = 0;
        for (int i = 0; i < 26; i++) {
            countUniqS += (countLettersInFirst[i] > 0);
        }
        for (int i = 0; i < 26; i++) {
            countUniqT += (countLettersInSecond[i] > 0);
        }
        if (countUniqS == 1 && countUniqT == 1) {
            for (int i = 0; i < 26; i++)
                if (countLettersInFirst[i] > 0 && countLettersInFirst[i] < countLettersInSecond[i]) {
                    ok = true;
                }
        }
        // проверив 3 случая, выводим ответ:
        cout << (ok ? "YES\n" : "NO\n");
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0)
        solve();
}

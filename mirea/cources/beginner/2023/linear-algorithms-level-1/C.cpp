#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // добавим элемент, который обломит возрастание в конце:
    a.push_back(0);
    n++;
    // теперь будем искать ответ
    int answ{1}, currLen{1};
    for (int i = 1; i < n; i++) {
        if (a[i-1] < a[i]) {
            currLen++;
        } else {
            answ = max(answ, currLen);
            currLen = 1;
        }
    }
    cout << answ << endl;
}
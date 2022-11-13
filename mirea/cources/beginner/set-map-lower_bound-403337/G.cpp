#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные + сразу вставляем в мультисет, чтобы искать там элементы:
    int n; cin >> n;
    vector<int> a(n);
    multiset<int64_t> mst;
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        mst.insert(a[i]);
    }
    // перебираем каждый удаляемый элемент
    vector<int> answer;
    for (int i = 0; i < n; i++) {
        // временно удаляем i-й элемент:
        mst.erase(mst.find(a[i]));
        sum -= a[i];
        // что-то делаем
        // должен быть элемент `x`, который равен сумме всех остальных
        // т.е. x == sum - x
        // значит 2 * x = sum => x = sum / 2
        // ищем элемент sum / 2
        if (sum % 2 == 0 && mst.find(sum / 2) != mst.end())
            answer.push_back(i+1);
        // возвращаем i-й элемент обратно:
        mst.insert(a[i]);
        sum += a[i];
    }
    // выводим ответ:
    cout << answer.size() << '\n';
    for (auto it : answer)
        cout << it << ' ';
}
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int getFixedError(const auto &before, const auto &after) {
    // вставляем в мультисет всё, что было до исправления бага:
    multiset<int> firstError(all(before));
    // удаляем всё, что осталось после исправления бага
    for (auto item : after)
        firstError.erase(firstError.find(item));
    // возвращаем ответ:
    assert(firstError.size() == 1u);
    return *firstError.begin();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), b(n-1), c(n-2);
    for (auto &it : a) cin >> it;
    for (auto &it : b) cin >> it;
    for (auto &it : c) cin >> it;
    cout << getFixedError(a,b) << '\n';
    cout << getFixedError(b,c) << '\n';
}
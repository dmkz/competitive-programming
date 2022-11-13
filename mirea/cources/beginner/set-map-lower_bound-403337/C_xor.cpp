// это второе решение: в нём вместо multiset используется bit_xor всех чисел
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int getFixedError(const auto &before, const auto &after) {
    // ответ - bit_xor всех чисел
    return accumulate(all(before), 0, bit_xor()) ^ accumulate(all(after), 0, bit_xor());
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
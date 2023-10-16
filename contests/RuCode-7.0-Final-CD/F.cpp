#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
auto factor(int n) {
    // делители
    vector<int> divs, stack;
    for (int x = 1; x * x <= n; x++)
        if (int y = n / x; x * y == n) {
            divs.push_back(x);
            if (y != x) stack.push_back(y);
        }
    while (isz(stack)) {
        divs.push_back(stack.back());
        stack.pop_back();
    }
    return divs;
}
int main() {
    int n; cin >> n;
    vector<int> b(n);
    for (auto &it : b)
        cin >> it;
    // ответ среди делителей b[0] - 1
    // проверим каждый делитель влоб
    vector<int> answ{1};
    for (int candidate : factor(b[0]-1)) {
        bool ok = 1;
        int prod = 1;
        for (int i = 0; ok && i < isz(b); i++) {
            // остаток от произведения элементов b на этот кандидат должен быть =1
            prod = int(prod * 1LL * b[i] % candidate);
            ok &= (prod == 1);
        }
        if (ok) answ.push_back(candidate);
    }
    for (auto it : answ)
        cout << it << endl;
}

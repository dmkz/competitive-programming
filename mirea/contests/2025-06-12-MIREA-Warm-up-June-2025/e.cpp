#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
void solve() {
    // читаем массив, запоминая позиции элементов, и будем работать в 1-индексации!
    int n; cin >> n;
    vi a(1+n), pos(1+n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    // обходим одну компоненту связности, обменивая рекурсивно, пока они не
    // встанут на свои места
    vi ops;
    function<void(int)> dfs = [&](int i) {
        if (a[i] == i)
            return;
        // надо поставить элемент "i" на позицию "i" обменяв с той позицией,
        // где сейчас стоит элемент i
        int j = pos[i];
        if (ops.empty()) // операций ещё не проводилось
            ops.push_back(i);
        if (ops.back() != i) {
            // прямо сейчас наш стек из операций не оканчивается элементом i
            // поэтому нужно обменять верхушку стека с элементом i
            int k = ops.back();
            a[i] ^= a[k];
            ops.push_back(i);
            a[k] ^= a[i];
            ops.push_back(k);
            a[i] ^= a[k];
            ops.push_back(i);
            pos[a[i]] = i;
            pos[a[k]] = k;
        }
        // теперь на верхушке стека элемент i
        // начинаем обмен
        a[j] ^= a[i];
        ops.push_back(j);
        a[i] ^= a[j];
        ops.push_back(i);
        a[j] ^= a[i];
        ops.push_back(j);
        pos[a[i]] = i;
        pos[a[j]] = j;
        // теперь на позиции i стоит элемент i, надо продолжить
        // с позиции j (так как именно оттуда мы забрали элемент)
        dfs(j);
    };
    // запускаем обход всех циклов, рекурсивно
    for (int i = 1; i <= n; i++)
        dfs(i);
    // выводим ответ:
    reverse(ops.begin(), ops.end());
    for (int i = 0; i < isz(ops); i++) {
        if (i > 0)
            std::cout << " ^= ";
        std::cout << "a[" << ops[i] << "]";
    }
    std::cout << ";\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Fenwick {
    
    vector<T> data;
    
    Fenwick(int n = 0) : data(n, 0) { }
    
    void inc(int p, T delta) {
        for (int i = p; i < (int)data.size(); i |= i+1)
            data[i] += delta;
    }
    
    T sum(int r) {
        T answ{};
        for (int i = r; i >= 0; i = (i & (i+1)) - 1)
            answ += data[i];
        return answ;
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    Fenwick<int> s(n + 1);
    for (int i = 0; i < n; i++) {
        int pi; cin >> pi;
        cout << i - s.sum(pi) << endl; // количество больших
        s.inc(pi, +1); // вставка
    }
    cout << endl;
}
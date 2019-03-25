#include <bits/stdc++.h>
#include "FastIO.hpp"

typedef long long ll;
typedef long double ld;

int main() {
    FastIO::Reader cin;
    FastIO::Writer cout;
    cout.setprecision(4);
    std::stack<ll> stack;
    for (ll v; cin >> v; stack.push(v));
    while (!stack.empty()) {
        cout << std::sqrt((ld)(stack.top())) << '\n';
        stack.pop();
    }
    return 0;
}
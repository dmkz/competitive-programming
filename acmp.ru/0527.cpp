#include <iostream>
#include <cassert>

typedef long long ll;

bool solve(ll a, ll b, ll c, ll d) {
    if (a == c && b == d) return true;
    while (b != 0) {
        if (b > a) {
            std::swap(b, a);
            continue;
        }
        ll rem = a % b;
        if (b == d && c <= a && c >= rem && (a-c) % b == 0) {
            return true;
        }
        a = rem;
    }
    return a == c && b == d;
}

int main() {
    int nQ; std::cin >> nQ;
    while (nQ--) {
        ll a, b, c, d; 
        std::cin >> a >> b >> c >> d;
        std::cout << (solve(a, b, c, d) ? "YES\n" : "NO\n");
    }
    return 0;
}
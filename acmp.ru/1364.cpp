/*
    Задача: 1364. Водолей
    Решение: диофантово уравнение, целочисленная арифметика, O(n)
*/
#include <bits/stdc++.h>
template<const bool out>
bool solve(int a, int b, const int n) {
    // Diophantine equation is x * a + y * b == n, solution exists if n % gcd(a,b) == 0
    int gcd = std::__gcd(a,b);
    if (n % gcd != 0 || n > std::max(a,b)) {
        out && std::cout << "Impossible" << std::endl;
        return false;
    }
    char ca = 'A', cb = 'B';
    if (a > b) {
        std::swap(a,b);
        std::swap(ca, cb);
    }
    int sa = 0, sb = 0;
    while (sa != n && sb != n) {
        if (sa == 0) {
            out && std::cout << ">" << ca << "\n";
            sa = a;
        } else if (sb == b) {
            out && std::cout << cb << ">" << "\n";
            sb = 0;
        } else {
            out && std::cout << ca << ">" << cb << "\n";
            const int delta = std::min(sa, b - sb);
            sa -= delta;
            sb += delta;
        }
    }
    return true;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int a, b, n;
    while (std::cin >> a >> b >> n) { solve<1>(a,b,n); }
    return 0;
}
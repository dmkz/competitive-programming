#include <bits/stdc++.h>
int main() {
    int n,b,p;
    std::cin >> n >> b >> p;
    // каждый матч даёт 2*b+1 бутылок (b каждому участнику и 1 судье)
    // число полотенец n*p - константа
    int bottles{}, towels = n * p;
    while (n > 1) {
        int power = std::__lg(n);
        int participants = (1 << power);
        int numFights = participants / 2;
        bottles += numFights * (2 * b + 1);
        n = (n - participants) + numFights;
    }
    std::cout << bottles << ' ' << towels << '\n';
}

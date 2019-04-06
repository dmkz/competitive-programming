/*
    Задача: 898. Ленточка
    
    Решение: рекурсия, динамическое программирование, O(k * n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef long long ll;
char solve(int n, ll x, const std::string& s) {
    const ll mid = (ll(1) << (n - 1));
    if (mid == x) { return s[n-1] == 'Z' ? 'K' : 'O'; }
    if (x < mid) { return solve(n-1, x, s); }
    return char('K'-solve(n-1, mid - (x - mid), s)+'O');
}
int main() {
    int n; std::string s; 
    while (std::cin >> n >> s) {
        int q; std::cin >> q;
        std::reverse(s.begin(), s.end());
        while (q--) {
            ll x; std::cin >> x;
            std::cout << solve(n, (ll(1) << n) - x, s);
        }
        std::cout << std::endl;
    }
    return 0;
}
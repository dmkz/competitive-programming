/*
    Задача: 902. Ленточка-2
    
    Решение: динамическое программирование, рекурсия, строки, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
std::string solve(std::string& s) {
    if (isz(s) == 1) { return s[0] == 'O' ? "P" : "Z"; }
    for (int i = 0, j = isz(s)-1; i < j; i++,--j) {
        if (s[i] != char('O' + 'K' - s[j])) {
            return "NO";
        }
    }
    int n = isz(s);
    assert(n % 2 == 1);
    for (int i = 0; i < n / 2; ++i) { s.pop_back(); }
    auto back = s.back(); s.pop_back();
    auto ret = solve(s);
    if (ret == "NO") { return "NO"; }
    else { return (back == 'O' ? "P" : "Z") + ret; }
}
int main() {
    int n; std::string s; 
    while (std::cin >> n >> s) { std::reverse(all(s)); std::cout << solve(s) << "\n"; }
    return 0;
}
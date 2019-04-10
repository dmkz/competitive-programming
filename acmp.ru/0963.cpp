#include <bits/stdc++.h>
/*
    Задача: 963. Морфизм
    
    Решение: рекурсия, разделяй и властвуй, мемоизация, строки, std::map, O(log(k) * p)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#define isz(x) (int)(x).size()
typedef std::vector<std::string> vs;
typedef std::pair<std::string, int> psi;
std::map<psi, std::string> cache;
std::string solve(const vs& f, std::string x, const int k, const int w) {
    if (isz(x) > w) { x.resize(w); }
    if (k == 0) { return x; }
    if (k == 1) {
        std::string answ;
        for (auto it : x) {
            answ += f[it];
            if (isz(answ) > w) {
                answ.resize(w);
                break;
            }
        }
        return answ;
    }
    auto key = psi(x, k);
    auto it = cache.find(key);
    if (it == cache.end()) {
        return cache[key] = solve(f, solve(f, x, k / 2, w), k - k / 2, w);
    }
    return it->second;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n, k, p;
    while (std::cin >> n >> k >> p) {
        std::string x; std::cin >> x;
        vs f(256);
        for (char c = 'A'; c < 'A' + n; ++c) { std::cin >> f[c]; }
        cache.clear();
        x = solve(f, x, k, 20);
        if (isz(x) > p-1) { std::cout << x[p-1] << std::endl; }
        else { std::cout << "-" << std::endl; }
    }
    return 0;
}
/*
    Задача: 813. Игра в 24
    
    Решение: перебор, рекурсия, O(n!*3^n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
bool ok;
void brute(vi arr) {
    if (isz(arr) == 1) {
        ok = ok || (arr[0] == 24);
        return;
    }
    for (int i = 0; i < isz(arr); ++i) {
        for (int j = i + 1; j < isz(arr); ++j) {
            auto fi = arr[i];
            auto se = arr[j];
            arr.erase(arr.begin()+j);
            arr[i] = fi * se;
            brute(arr);
            arr[i] = fi - se;
            brute(arr);
            arr[i] = fi + se;
            brute(arr);
            arr[i] = fi;
            arr.insert(arr.begin()+j, se);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    vi arr(4); for (auto &it : arr) { std::cin >> it; }
    brute(arr);
    std::cout << (ok ? "YES\n" : "NO\n");
    return 0;
}
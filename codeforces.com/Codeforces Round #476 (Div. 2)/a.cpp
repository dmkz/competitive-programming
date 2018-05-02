#include <bits/stdc++.h>

using namespace std;

typedef int64_t Int;

int main() {
    Int k, n, s, p;
    cin >> k >> n >> s >> p;
    // p - в одной пачке
    // s - самолетиков из одного листа
    
    // Сколько нужно листов одному человеку?
    Int need_one = (n + s-1) / s;
    // Сколько нужно пачек всем людям?
    Int need_all = (need_one * k + p - 1) / p;
    std::cout << need_all << std::endl;
    return 0;
}
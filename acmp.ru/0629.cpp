/*
    Задача: 629. Сочетания
    
    Решение: комбинаторика, биномиальные коэффициенты, сочетания, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

typedef long long ll;

int main() {
    
    std::vector<std::vector<ll>> bin(27, std::vector<ll>(27, 1));
    for (int n = 2; n < 27; ++n) {
        for (int k = 0; k <= n; ++k) {
            bin[n][k] = (k > 0 ? bin[n-1][k-1] : 0) + (k <= n-1 ? bin[n-1][k] : 0);
        }
    }
    
    std::function<void(int,int,int,ll)> solve = [&bin, &solve](int s, int n, int len, ll need) {
        if (len == 0 || need == 0 || s > n) {
            return;
        }
        if (bin[n-s][len-1] >= need) {
            std::cout << char('a'+s-1);
            solve(s+1, n, len-1, need);
        } else {
            solve(s+1, n, len, need - bin[n-s][len-1]);
        }
    };
    
    int n, len; ll need;
    std::cin >> n >> len >> need;
    solve(1,n,len,need);
    return 0;
}
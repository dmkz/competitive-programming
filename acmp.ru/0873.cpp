/*
    Задача: 873. Шифр "Решетка"
    
    Решение: быстрое возведение в степень, комбинаторика, O(log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int pow(int a, ll k, int mod) {
    int ret = 1 % mod;
    while (k > 0) {
        if (k & 1) {
            ret = int(1LL * ret * a % mod);
        }
        k >>= 1;
        a = int (1LL * a * a % mod);
    }
    return ret;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << pow(4 % m, ll(n) * n / 4, m) << std::endl;
    return 0;
}
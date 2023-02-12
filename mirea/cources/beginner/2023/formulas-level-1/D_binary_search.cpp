#include <bits/stdc++.h>
using namespace std;
int main() {
    int64_t n; cin >> n;
    // блоки:
    // 1
    // 1 2
    // 1 2 3
    // 1 2 3 4
    // 1 ... k
    // 1 ... k k+1
    // найдём макс k такое, что n лежит внутри его блока
    // в каждом i-м блоке ровно i чисел
    // получается 1 + 2 + 3 + ... + k >= n
    // k * (k+1) / 2 >= n
    // границы бинпоиска:
    // low НЕ УДОВЛЕТВОРЯЕТ неравенству
    // high УДОВЛЕТВОРЯЕТ неравенству
    int64_t low = 0, high = (int64_t)1e9;
    while (high - low > 1) {
        int64_t k = (low + high) / 2;
        if (k * (k+1) / 2 >= n) high = k;
        else low = k;
    }
    int64_t k = low; // ответ равен левой границе бинпоиска
    cout << n - k*(k+1)/2 << endl;
}
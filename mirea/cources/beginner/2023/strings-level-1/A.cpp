#include <bits/stdc++.h>
using namespace std;
int main() {
    // переберём все счастливые числа и найдём ближайшее
    // счастливых чисел 9 * 10, где:
    //  9 = число способов выбрать ненулевую цифру
    // 10 = число способов выбрать её позицию
    int64_t n; cin >> n;
    int64_t best = 2'000'000'000; // берём хороший год, который точно
                                  // строго больше любого возможного n
    for (int pos = 0; pos <= 9; pos++) {
        for (char digit = '1'; digit <= '9'; digit++) {
            // создаём число как строку:
            std::string number(10, '0');
            number[pos] = digit;
            // конвертим его в тип long long:
            int64_t x = stoll(number);
            // обновляем ответ:
            if (x > n && best - n > x - n)
                best = x;
        }
    }
    cout << best-n << '\n';
}
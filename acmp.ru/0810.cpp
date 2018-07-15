/*
    "Число - 2": делители числа, простые числа
*/

#include <iostream>

int get(int value, int s1, int t1, int s2, int t2) {
    bool flag = false;
    while (!flag) {
        ++value;
        flag = true;
        for (int i = 1; i * i <= value; ++i) {
            const int j = value / i;
            if (i * j == value && (
                (s1 <= i && i <= t1 && s2 <= j && j <= t2) ||
                (s1 <= j && j <= t1 && s2 <= i && i <= t2))
            ) {
                flag = false;
                break;
            }
        }
    }
    return value;
}

int main() {
    int s1, t1, s2, t2;
    std::cin >> s1 >> t1 >> s2 >> t2;
    if (s1 == 1 && s2 == 1) {
        std::cout << get(std::max(t1, t2), s1, t1, s2, t2);
    } else if (s1 == 1) {
        std::cout << get(t2, s1, t1, s2, t2);
    } else if (s2 == 1) {
        std::cout << get(t1, s1, t1, s2, t2);
    } else {
        std::cout << 1LL*s1*s2+1;
    }
    return 0;
}
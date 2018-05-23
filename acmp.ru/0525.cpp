#include <iostream>
#include <functional>

int main() {
    int n; std::cin >> n;
    static int answ[1001][20];
    for (int i = 0; i < 1001; ++i) {
        for (int j = 0; j < 20; ++j) {
            answ[i][j] = (i == 0 || j == 0) ? 1 : -1;
        }
    }
    std::function<int(int, int)> get=[&](const int number, const int pow) {
        if (answ[number][pow] == -1) {
            int count = 0;
            for (int p = pow; p >= 0; --p) {
                if (number - (1 << p) >= 0) {
                    auto add = get(number-(1 << p), p);
                    count += add;
                }
            }
            answ[number][pow] = count;
        }
        return answ[number][pow];
    };
    std::cout << get(n, 19);
    return 0;
}
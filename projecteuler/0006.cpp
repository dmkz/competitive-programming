#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= 100; ++i) {
        sum1 += i * i;
        sum2 += i;
    }
    sum2 *= sum2;
    std::cout << sum1 - sum2;
    return 0;
}